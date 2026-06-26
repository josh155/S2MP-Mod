#include "pch.h"
#include "Demonware.hpp"
#include "DemoByteBuffer.hpp"
#include "DemoPlayback.hpp"
#include "structs.h"
#include "Hook.hpp"
#include "Console.hpp"
#include "DevDef.h"

#include <unordered_set>

// Minimal demonware loopback emulation for demo playback. See Demonware.hpp.
//
// Verified game symbols (IDA MCP, _b = RVA - 0x1000):
//   SV_Cmd_TokenizeString     0x64B070_b (RVA 0x64C070)
//   SV_Cmd_EndTokenizedString 0x64B030_b (RVA 0x64C030)
//   sv_cmd_args  (CmdArgs)    0xAA753C0_b (RVA 0xAA763C0)
namespace demonware
{
	namespace
	{
		// jenkins one-at-a-time (matches s1/s2-mod base_server address hashing)
		uint32_t jenkins_hash(const std::string& key)
		{
			uint32_t hash = 0;
			for (const char c : key)
			{
				hash += static_cast<uint8_t>(c);
				hash += (hash << 10);
				hash ^= (hash >> 6);
			}
			hash += (hash << 3);
			hash ^= (hash >> 11);
			hash += (hash << 15);
			return hash;
		}

		using SV_Cmd_TokenizeString_t = void(__fastcall*)(const char* text);
		using SV_Cmd_EndTokenizedString_t = void(__fastcall*)();
	}

	// ===== base_server =====
	base_server::base_server(std::string name) : name_(std::move(name))
	{
		this->address_ = jenkins_hash(this->name_);
	}

	const std::string& base_server::get_name() const { return this->name_; }
	uint32_t base_server::get_address() const { return this->address_; }

	// ===== udp_server =====
	udp_server::endpoint_data::endpoint_data(const SOCKET sock, const sockaddr* addr, const int size)
	{
		if (size != static_cast<int>(sizeof(this->address)))
		{
			throw std::runtime_error("Invalid endpoint size");
		}
		this->socket = sock;
		std::memcpy(&this->address, addr, sizeof(this->address));
	}

	void udp_server::handle_input(const char* buf, size_t size, endpoint_data endpoint)
	{
		in_queue_.access([&](in_queue& queue)
		{
			in_packet p;
			p.data = std::string{ buf, size };
			p.endpoint = std::move(endpoint);
			queue.emplace(std::move(p));
		});
	}

	size_t udp_server::handle_output(SOCKET socket, char* buf, size_t size, sockaddr* address, int* addrlen)
	{
		return out_queue_.access<size_t>([&](socket_queue_map& map) -> size_t
		{
			const auto entry = map.find(socket);
			if (entry == map.end() || entry->second.empty())
			{
				return 0;
			}

			auto data = std::move(entry->second.front());
			entry->second.pop();

			const auto copy_size = (std::min)(size, data.data.size());
			std::memcpy(buf, data.data.data(), copy_size);
			std::memcpy(address, &data.address, sizeof(data.address));
			*addrlen = sizeof(data.address);

			return copy_size;
		});
	}

	bool udp_server::pending_data(SOCKET socket)
	{
		return out_queue_.access<bool>([&](const socket_queue_map& map)
		{
			const auto entry = map.find(socket);
			return entry != map.end() && !entry->second.empty();
		});
	}

	void udp_server::send(const endpoint_data& endpoint, std::string data)
	{
		out_queue_.access([&](socket_queue_map& map)
		{
			out_packet p;
			p.data = std::move(data);
			p.address = endpoint.address;
			map[endpoint.socket].emplace(std::move(p));
		});
	}

	void udp_server::frame()
	{
		while (true)
		{
			in_packet packet{};
			const auto got = in_queue_.access<bool>([&](in_queue& queue)
			{
				if (queue.empty()) return false;
				packet = std::move(queue.front());
				queue.pop();
				return true;
			});

			if (!got) break;
			this->handle(packet.endpoint, std::move(packet.data));
		}
	}

	// ===== theater_server =====
	namespace theater
	{
		theater_server* instance = nullptr;

		theater_server::theater_server(std::string name) : udp_server(std::move(name))
		{
			instance = this;
		}

		bool theater_server::connected()
		{
			std::lock_guard<std::mutex> lock(this->endpoint_mutex_);
			return this->client_endpoint_.has_value();
		}

		void theater_server::stop()
		{
			std::lock_guard<std::mutex> lock(this->endpoint_mutex_);
			this->client_endpoint_ = std::nullopt;
		}

		void theater_server::handle_get_info(const endpoint_data& endpoint, const std::string&)
		{
			auto reader = demo_playback::get_current_demo_reader();
			if (!reader)
			{
				Console::printf("[demo] theater: no demo reader ready for getInfo");
				return;
			}

			auto args = *reinterpret_cast<CmdArgs*>(0xAA753C0_b);
			std::string challenge;
			if (args.argc[args.nesting] >= 2)
			{
				challenge = args.argv[args.nesting][1];
			}

			std::string response = "infoResponse\n";
			response += "\\challenge\\" + challenge;
			response += "\\isPrivate\\0";
			response += "\\playmode\\2";
			response += "\\hostname\\Demo_Server";
			response += "\\gamename\\S2";
			response += "\\sv_maxclients\\18";
			response += "\\gametype\\" + reader->get_mode();
			response += "\\sv_motd\\Loading Demo";
			response += "\\xuid\\110000139E3FC15";
			response += "\\mapname\\" + reader->get_map_name();
			response += "\\clients\\1";
			response += "\\bots\\0";
			response += "\\protocol\\1";
			response += "\\sv_running\\1";
			response += "\\dedicated\\1";
			response += "\\shortversion\\0.0.1";

			demo::byte_buffer buffer;
			buffer.set_use_data_types(false);
			buffer.write_int32(-1);
			buffer.write_string(response);

			this->send(endpoint, buffer.get_buffer());
		}

		void theater_server::handle_get_challenge(const endpoint_data& endpoint, const std::string&)
		{
			demo::byte_buffer buffer;
			buffer.set_use_data_types(false);
			buffer.write_int32(-1);
			buffer.write_string("challengeResponse");
			buffer.write_int32(rand());

			this->send(endpoint, buffer.get_buffer());
		}

		void theater_server::handle_connect(const endpoint_data& endpoint, const std::string&)
		{
			Console::printf("[demo] theater: received connection request");
			std::lock_guard<std::mutex> lock(this->endpoint_mutex_);
			this->client_endpoint_ = endpoint;
		}

		void theater_server::handle_connectionless_packet(const endpoint_data& endpoint, const std::string& packet)
		{
			demo::byte_buffer buffer(packet);
			buffer.set_use_data_types(false);

			int tick;
			std::string str;
			buffer.read_int32(&tick);
			buffer.read_string(&str);

			reinterpret_cast<SV_Cmd_TokenizeString_t>(0x64B070_b)(str.c_str());

			auto args = *reinterpret_cast<CmdArgs*>(0xAA753C0_b);
			if (args.argc[args.nesting] > 0)
			{
				const auto* command = args.argv[args.nesting][0];
				if (std::strcmp("getInfo", command) == 0)
				{
					this->handle_get_info(endpoint, packet);
				}
				else if (std::strcmp("getchallenge", command) == 0)
				{
					this->handle_get_challenge(endpoint, packet);
				}
				else if (std::strcmp("connect", command) == 0)
				{
					this->handle_connect(endpoint, packet);
				}
			}

			reinterpret_cast<SV_Cmd_EndTokenizedString_t>(0x64B030_b)();
		}

		void theater_server::handle(const endpoint_data& endpoint, const std::string& packet)
		{
			demo::byte_buffer buffer(packet);
			buffer.set_use_data_types(false);

			int tick;
			buffer.read_int32(&tick);

			if (tick == -1)
			{
				this->handle_connectionless_packet(endpoint, packet);
			}
		}

		void theater_server::frame()
		{
			auto reader = demo_playback::get_current_demo_reader();

			std::optional<endpoint_data> endpoint;
			{
				std::lock_guard<std::mutex> lock(this->endpoint_mutex_);
				endpoint = this->client_endpoint_;
			}

			if (endpoint && reader)
			{
				while (true)
				{
					auto msg = reader->dequeue_server_message();
					if (!msg) break;
					this->send(*endpoint, *msg);
				}
			}

			udp_server::frame();
		}
	}

	// ===== UDP server registry (single "demo" server) =====
	namespace
	{
		std::unordered_map<uint32_t, std::unique_ptr<udp_server>> udp_servers;

		udp_server* find_udp_server(const std::string& name)
		{
			const auto it = udp_servers.find(jenkins_hash(name));
			return it == udp_servers.end() ? nullptr : it->second.get();
		}

		udp_server* find_udp_server(const uint32_t address)
		{
			const auto it = udp_servers.find(address);
			return it == udp_servers.end() ? nullptr : it->second.get();
		}
	}

	// ===== WinSock hook layer =====
	namespace
	{
		std::atomic_bool exit_server{ false };
		utils::concurrency::container<std::unordered_map<SOCKET, bool>> blocking_sockets{};

		std::mutex addrinfo_mutex;
		std::unordered_set<void*> our_addrinfo;

		bool is_socket_blocking(const SOCKET socket, const bool def)
		{
			return blocking_sockets.access<bool>([&](std::unordered_map<SOCKET, bool>& map)
			{
				const auto entry = map.find(socket);
				return entry == map.end() ? def : entry->second;
			});
		}

		namespace io
		{
			using getaddrinfo_t = int(__stdcall*)(const char*, const char*, const addrinfo*, addrinfo**);
			using freeaddrinfo_t = void(__stdcall*)(addrinfo*);
			using gethostbyname_t = hostent*(__stdcall*)(const char*);
			using sendto_t = int(__stdcall*)(SOCKET, const char*, int, int, const sockaddr*, int);
			using recvfrom_t = int(__stdcall*)(SOCKET, char*, int, int, sockaddr*, int*);
			using closesocket_t = int(__stdcall*)(SOCKET);
			using ioctlsocket_t = int(__stdcall*)(SOCKET, long, u_long*);

			getaddrinfo_t _getaddrinfo = nullptr;
			freeaddrinfo_t _freeaddrinfo = nullptr;
			gethostbyname_t _gethostbyname = nullptr;
			sendto_t _sendto = nullptr;
			recvfrom_t _recvfrom = nullptr;
			closesocket_t _closesocket = nullptr;
			ioctlsocket_t _ioctlsocket = nullptr;

			int __stdcall getaddrinfo_stub(const char* name, const char* service, const addrinfo* hints, addrinfo** res)
			{
				udp_server* server = name ? find_udp_server(name) : nullptr;
				if (!server)
				{
					return _getaddrinfo(name, service, hints, res);
				}

				auto* address = new sockaddr{};
				auto* ai = new addrinfo{};

				auto* in_addr = reinterpret_cast<sockaddr_in*>(address);
				in_addr->sin_addr.s_addr = server->get_address();
				in_addr->sin_family = AF_INET;

				ai->ai_family = AF_INET;
				ai->ai_socktype = SOCK_DGRAM;
				ai->ai_addr = address;
				ai->ai_addrlen = sizeof(sockaddr);
				ai->ai_next = nullptr;
				ai->ai_canonname = const_cast<char*>(name);

				{
					std::lock_guard<std::mutex> lock(addrinfo_mutex);
					our_addrinfo.insert(ai);
				}

				*res = ai;
				return 0;
			}

			void __stdcall freeaddrinfo_stub(addrinfo* ai)
			{
				bool ours = false;
				{
					std::lock_guard<std::mutex> lock(addrinfo_mutex);
					const auto it = our_addrinfo.find(ai);
					if (it != our_addrinfo.end())
					{
						our_addrinfo.erase(it);
						ours = true;
					}
				}

				if (!ours)
				{
					_freeaddrinfo(ai);
					return;
				}

				delete ai->ai_addr;
				delete ai;
			}

			hostent* __stdcall gethostbyname_stub(const char* name)
			{
				udp_server* server = name ? find_udp_server(name) : nullptr;
				if (!server)
				{
					return _gethostbyname(name);
				}

				static thread_local in_addr address{};
				address.s_addr = server->get_address();

				static thread_local in_addr* addr_list[2]{};
				addr_list[0] = &address;
				addr_list[1] = nullptr;

				static thread_local hostent host{};
				host.h_name = const_cast<char*>(name);
				host.h_aliases = nullptr;
				host.h_addrtype = AF_INET;
				host.h_length = sizeof(in_addr);
				host.h_addr_list = reinterpret_cast<char**>(addr_list);

				return &host;
			}

			int __stdcall sendto_stub(SOCKET s, const char* buf, int len, int flags, const sockaddr* to, int tolen)
			{
				const auto* in_addr = reinterpret_cast<const sockaddr_in*>(to);
				auto* server = to ? find_udp_server(in_addr->sin_addr.s_addr) : nullptr;

				if (server)
				{
					server->handle_input(buf, len, { s, to, tolen });
					return len;
				}

				return _sendto(s, buf, len, flags, to, tolen);
			}

			int __stdcall recvfrom_stub(SOCKET s, char* buf, int len, int flags, sockaddr* from, int* fromlen)
			{
				if (is_socket_blocking(s, false))
				{
					return _recvfrom(s, buf, len, flags, from, fromlen);
				}

				size_t result = 0;
				for (auto& server : udp_servers)
				{
					if (server.second->pending_data(s))
					{
						result = server.second->handle_output(s, buf, static_cast<size_t>(len), from, fromlen);
					}
				}

				if (result)
				{
					return static_cast<int>(result);
				}

				return _recvfrom(s, buf, len, flags, from, fromlen);
			}

			int __stdcall closesocket_stub(SOCKET s)
			{
				blocking_sockets.access([&](std::unordered_map<SOCKET, bool>& map)
				{
					map.erase(s);
				});
				return _closesocket(s);
			}

			int __stdcall ioctlsocket_stub(SOCKET s, long cmd, u_long* argp)
			{
				if (static_cast<unsigned long>(cmd) == FIONBIO && argp)
				{
					blocking_sockets.access([&](std::unordered_map<SOCKET, bool>& map)
					{
						map[s] = (*argp == 0);
					});
				}
				return _ioctlsocket(s, cmd, argp);
			}
		}

		void server_main()
		{
			while (!exit_server)
			{
				for (auto& server : udp_servers)
				{
					server.second->frame();
				}
				std::this_thread::sleep_for(std::chrono::milliseconds(20));
			}
		}

		template <typename T>
		void hook_ws(HMODULE ws, const char* name, void* stub, T* original)
		{
			auto* proc = reinterpret_cast<void*>(GetProcAddress(ws, name));
			if (!proc || !Hook::create(name, proc, stub, reinterpret_cast<void**>(original)))
			{
				DEV_PRINTF("[demo] failed to hook ws2_32!%s", name);
			}
		}
	}

	void init()
	{
		// register the local "demo" theater server
		auto server = std::make_unique<theater::theater_server>("demo");
		udp_servers[server->get_address()] = std::move(server);

		HMODULE ws = GetModuleHandleA("ws2_32.dll");
		if (!ws) ws = LoadLibraryA("ws2_32.dll");
		if (!ws)
		{
			Console::printf("[demo] ws2_32 not available; demo playback disabled");
			return;
		}

		hook_ws(ws, "getaddrinfo", &io::getaddrinfo_stub, &io::_getaddrinfo);
		hook_ws(ws, "freeaddrinfo", &io::freeaddrinfo_stub, &io::_freeaddrinfo);
		hook_ws(ws, "gethostbyname", &io::gethostbyname_stub, &io::_gethostbyname);
		hook_ws(ws, "sendto", &io::sendto_stub, &io::_sendto);
		hook_ws(ws, "recvfrom", &io::recvfrom_stub, &io::_recvfrom);
		hook_ws(ws, "closesocket", &io::closesocket_stub, &io::_closesocket);
		hook_ws(ws, "ioctlsocket", &io::ioctlsocket_stub, &io::_ioctlsocket);

		std::thread(&server_main).detach();
	}
}
