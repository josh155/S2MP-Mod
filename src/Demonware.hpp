#pragma once

// Minimal demonware loopback emulation, ported/trimmed from Airyzz s1-mod and
// s2-mod (only what demo PLAYBACK needs). The engine's `connect demo` is routed
// to an in-process UDP "theater" server via WinSock hooks; the server answers the
// connection handshake and feeds recorded server messages back through the engine's
// normal recvfrom/netchan path. See Demonware.cpp for the socket-hook layer.
//
// WinSock types (SOCKET, sockaddr_in, ...) come from pch.h (WinSock2 included there).
#include "Hook.hpp" // utils::concurrency::container

#include <string>
#include <queue>
#include <unordered_map>
#include <optional>
#include <mutex>

namespace demonware
{
	class base_server
	{
	public:
		base_server(std::string name);
		base_server(base_server&&) = delete;
		base_server(const base_server&) = delete;
		base_server& operator=(base_server&&) = delete;
		base_server& operator=(const base_server&) = delete;
		virtual ~base_server() = default;

		const std::string& get_name() const;
		uint32_t get_address() const;

		virtual void frame() = 0;

	private:
		std::string name_;
		std::uint32_t address_ = 0;
	};

	class udp_server : public base_server
	{
	public:
		struct endpoint_data
		{
			SOCKET socket{};
			sockaddr_in address{};

			endpoint_data() = default;
			endpoint_data(SOCKET sock, const sockaddr* addr, int size);
		};

		using base_server::base_server;

		void handle_input(const char* buf, size_t size, endpoint_data endpoint);
		size_t handle_output(SOCKET socket, char* buf, size_t size, sockaddr* address, int* addrlen);
		bool pending_data(SOCKET socket);

		void frame() override;

	protected:
		virtual void handle(const endpoint_data& endpoint, const std::string& data) = 0;
		void send(const endpoint_data& endpoint, std::string data);

	private:
		struct in_packet
		{
			std::string data;
			endpoint_data endpoint;
		};
		struct out_packet
		{
			std::string data;
			sockaddr_in address;
		};

		using in_queue = std::queue<in_packet>;
		using out_queue = std::queue<out_packet>;
		using socket_queue_map = std::unordered_map<SOCKET, out_queue>;

		utils::concurrency::container<in_queue> in_queue_;
		utils::concurrency::container<socket_queue_map> out_queue_;
	};

	namespace theater
	{
		class theater_server : public udp_server
		{
		public:
			theater_server(std::string name);

			void frame() override;
			void stop();
			bool connected();

		private:
			void handle(const endpoint_data& endpoint, const std::string& packet) override;
			void handle_connectionless_packet(const endpoint_data& endpoint, const std::string& packet);
			void handle_get_info(const endpoint_data& endpoint, const std::string& packet);
			void handle_get_challenge(const endpoint_data& endpoint, const std::string& packet);
			void handle_connect(const endpoint_data& endpoint, const std::string& packet);

			std::mutex endpoint_mutex_;
			std::optional<endpoint_data> client_endpoint_;
		};

		extern theater_server* instance;
	}

	void init();
}
