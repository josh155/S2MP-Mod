#include "pch.h"
#include "DemoPlayback.hpp"
#include "DemoData.hpp"

#include "FuncPointers.h"
#include "Console.hpp"
#include "GameUtil.hpp"
#include "Hook.hpp"
#include "Demonware.hpp"

#include <mutex>
#include <memory>
#include <atomic>
#include <thread>
#include <chrono>
#include <filesystem>

// Ported from Airyzz/s1-mod via s2-mod (demo_playback.cpp), adapted to S2MP-Mod.
//
// === Playback design (theater loopback, matches s1/s2-mod) ===================
// demo_play opens the reader and runs `connect demo`. The minimal demonware layer
// (Demonware.cpp) routes that connection to an in-process theater_server, which
// answers the getInfo/getchallenge/connect handshake and then feeds the recorded
// server messages back through the engine's normal recvfrom/netchan path. This
// pump only advances the reader (read_frame) once the theater reports connected;
// the theater drains server_queue on the demonware thread.
//
// View following uses CL_GetPredictedPlayerInformationForServerTime (verified
// 0x461650_b): on playback we overwrite the predicted origin/velocity with the
// recorded values so the camera follows the recording.
namespace demo_playback
{
	namespace
	{
		// playerState_s offsets confirmed in IDA (CL_Get... writes origin to +132,
		// velocity to +144).
		constexpr size_t PS_ORIGIN_OFFSET = 132;
		constexpr size_t PS_VELOCITY_OFFSET = 144;

		std::mutex read_lock;       // guards demo_reader::server_queue
		std::mutex reader_mutex;    // guards the current_reader shared_ptr lifetime
		std::atomic<bool> playing_flag{ false };
		std::atomic<bool> pump_running{ false };
		int prevFrameTime = 0;

		dvar_t* demo_paused = nullptr;
	}

	// Owned via shared_ptr so the worker thread can hold a local reference for the
	// duration of an access while the main thread swaps or clears the global.
	std::shared_ptr<demo_reader> current_reader;

	demo_reader::demo_reader(std::string filepath)
	{
		time = 0;
		firstMessageTime = -1;
		offsetTime = 0;
		sequenceNumber = 0;
		firstMessageFileOffset = 0;

		stream = std::ifstream(filepath, std::ios::binary | std::ifstream::in);

		std::memset(&last_client_data, 0, sizeof(last_client_data));
		std::memset(&frames, 0, sizeof(frames));

		if (!stream.is_open())
		{
			Console::printf("[demo] failed to open demo file: %s", filepath.data());
			return;
		}

		int mapNameLength = 0;
		stream.read(reinterpret_cast<char*>(&mapNameLength), sizeof(mapNameLength));
		if (mapNameLength > 0 && mapNameLength < 1024)
		{
			map.resize(mapNameLength);
			stream.read(map.data(), mapNameLength);
		}

		int modeLength = 0;
		stream.read(reinterpret_cast<char*>(&modeLength), sizeof(modeLength));
		if (modeLength > 0 && modeLength < 1024)
		{
			mode.resize(modeLength);
			stream.read(mode.data(), modeLength);
		}

		Console::printf("[demo] reader created: map='%s' mode='%s'", map.data(), mode.data());

		firstMessageFileOffset = stream.tellg();
	}

	bool demo_reader::is_open()
	{
		return stream.is_open();
	}

	std::optional<demo_data::demo_client_data_t> demo_reader::get_client_data_for_time(int t)
	{
		auto frame = frames[t & 255];
		if (frame.predictedDataServerTime == t)
		{
			return frame;
		}

		return std::nullopt;
	}

	std::optional<std::string> demo_reader::dequeue_server_message()
	{
		std::lock_guard<std::mutex> lock(read_lock);
		if (server_queue.empty())
		{
			return std::nullopt;
		}

		auto msg = server_queue.front();
		server_queue.pop_front();
		return msg;
	}

	std::string demo_reader::get_map_name()
	{
		return map;
	}

	std::string demo_reader::get_mode()
	{
		return mode;
	}

	bool demo_reader::peek_next_message_time(int& out)
	{
		out = 0;
		const auto pos = stream.tellg();
		stream.read(reinterpret_cast<char*>(&out), sizeof(out));
		if (!stream)
		{
			stream.clear();
			stream.seekg(pos);
			return false;
		}

		stream.seekg(pos);
		return true;
	}

	void demo_reader::read_server_message()
	{
		int size = 0;
		std::string data;
		stream.read(reinterpret_cast<char*>(&size), sizeof(size));
		if (size < 0 || size >(64 * 1024 * 1024))
		{
			return;
		}

		data.resize(size);
		stream.read(data.data(), size);

		if (size >= static_cast<int>(sizeof(int)))
		{
			const int originalSeq = *reinterpret_cast<int*>(data.data());
			if (originalSeq != -1)
			{
				// Rewrite the sequence number with our own monotonic counter so that
				// rewinding the demo doesn't make the engine drop "past" packets.
				*reinterpret_cast<int*>(data.data()) = sequenceNumber;
				sequenceNumber += 1;
			}
		}

		int splitSize = 0;
		std::string splitData;
		stream.read(reinterpret_cast<char*>(&splitSize), sizeof(splitSize));
		if (splitSize > 0 && splitSize < (64 * 1024 * 1024))
		{
			splitData.resize(splitSize);
			stream.read(splitData.data(), splitSize);
		}

		std::string result = data + splitData;

		// Called only from read_message() <- read_frame(), which already holds
		// read_lock. Do NOT lock again here (std::mutex is non-recursive).
		server_queue.push_back(std::move(result));
	}

	void demo_reader::read_client_data()
	{
		int size = 0;
		stream.read(reinterpret_cast<char*>(&size), sizeof(size));

		if (size != static_cast<int>(sizeof(demo_data::demo_client_data_t)))
		{
			Console::printf("[demo] invalid client data size, skipping %d bytes", size);
			stream.seekg(size, std::ios_base::cur);
			return;
		}

		demo_data::demo_client_data_t data{};
		stream.read(reinterpret_cast<char*>(&data), sizeof(data));
		frames[data.predictedDataServerTime & 255] = data;
	}

	void demo_reader::read_message()
	{
		int t = 0;
		stream.read(reinterpret_cast<char*>(&t), sizeof(t));

		int type = 0;
		stream.read(reinterpret_cast<char*>(&type), sizeof(type));

		if (type == demo_data::DemoPacketType::SERVER_MESSAGE)
		{
			read_server_message();
		}
		else if (type == demo_data::DemoPacketType::CLIENT_DATA)
		{
			read_client_data();
		}
	}

	void demo_reader::read_frame(int ms)
	{
		std::lock_guard<std::mutex> lock(read_lock);
		time += ms;

		while (true)
		{
			if (!stream || stream.eof())
			{
				break;
			}

			int msg_time = 0;
			if (!peek_next_message_time(msg_time))
			{
				break;
			}

			// -1 (0xffffffff) markers are out-of-band packets that play immediately.
			if (msg_time == -1)
			{
				read_message();
				continue;
			}

			if (msg_time > 0 && firstMessageTime <= 0)
			{
				firstMessageTime = msg_time;
				time = msg_time;
			}

			if (msg_time > time)
			{
				break;
			}

			read_message();
		}
	}

	void demo_reader::close()
	{
		stream.close();
	}

	void demo_reader::restart()
	{
		std::lock_guard<std::mutex> lock(read_lock);
		stream.clear();
		stream.seekg(firstMessageFileOffset, std::ios_base::beg);
		time = 0;
		firstMessageTime = -1;
		sequenceNumber = 0;
		server_queue.clear();
	}

	void demo_reader::jump_to(int target_time)
	{
		if (target_time < time)
		{
			restart();
		}

		time = target_time;
		read_frame(0);
	}

	int demo_reader::get_time()
	{
		return time;
	}

	bool is_paused()
	{
		return demo_paused && demo_paused->current.enabled;
	}

	bool is_playing()
	{
		return playing_flag.load();
	}

	std::shared_ptr<demo_reader> get_current_demo_reader()
	{
		std::lock_guard<std::mutex> lock(reader_mutex);
		return current_reader;
	}

	// CL_GetPredictedPlayerInformationForServerTime (verified 0x461650_b)
	// During playback, inject the recorded local-player origin/velocity so the view
	// follows the recording. Milestone 1: origin + velocity (confirmed offsets).
	utils::hook::detour cl_get_predicted_player_information_for_server_time_hook;
	__int64 cl_get_predicted_player_information_for_server_time_stub(void* clientActive, int serverTime, void* playerState)
	{
		const auto result = cl_get_predicted_player_information_for_server_time_hook.invoke<__int64>(clientActive, serverTime, playerState);

		auto reader = get_current_demo_reader();
		if (reader && playerState)
		{
			const auto val = reader->get_client_data_for_time(serverTime);
			if (val)
			{
				auto* ps = reinterpret_cast<char*>(playerState);
				std::memcpy(ps + PS_ORIGIN_OFFSET, val->origin, sizeof(val->origin));
				std::memcpy(ps + PS_VELOCITY_OFFSET, val->velocity, sizeof(val->velocity));
			}
		}

		return result;
	}

	// Per-frame pump: advance the reader so it populates server_queue. The recorded
	// messages are drained and fed to the engine by the demonware theater_server
	// (on the demonware thread) through the normal recvfrom/netchan path. We only
	// advance once the engine has actually connected to the theater server, matching
	// s2-mod (otherwise we'd read past the handshake).
	static void pump_once()
	{
		auto reader = get_current_demo_reader();
		if (!reader || is_paused() || !playing_flag.load())
		{
			return;
		}

		if (!demonware::theater::instance || !demonware::theater::instance->connected())
		{
			return;
		}

		const int now = Functions::_Sys_Milliseconds ? Functions::_Sys_Milliseconds() : 0;
		int delta = now - prevFrameTime;
		prevFrameTime = now;

		if (delta < 0 || delta > 500)
		{
			delta = 16;
		}

		if (Functions::_Com_TimeScaleMsec)
		{
			delta = Functions::_Com_TimeScaleMsec(delta);
		}

		reader->read_frame(delta);
	}

	static void pump_thread()
	{
		while (pump_running.load())
		{
			pump_once();
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
		}
	}

	void stop_playback()
	{
		{
			std::lock_guard<std::mutex> lock(reader_mutex);
			current_reader.reset();
			playing_flag = false;
		}

		if (demonware::theater::instance)
		{
			demonware::theater::instance->stop();
		}
	}

	// ===== Commands (S2MP-Mod free-function style; args via GameUtil::getCmdArgs) =====
	static void demo_play_f()
	{
		CmdArgs* args = GameUtil::getCmdArgs();
		if (!args)
		{
			return;
		}
		const int nest = args->nesting;
		if (args->argc[nest] < 2)
		{
			Console::printf("usage: demo_play <file.demo>");
			return;
		}

		const auto* file = args->argv[nest][1];
		const auto filepath = "demos/" + std::string(file);

		if (!std::filesystem::exists(filepath))
		{
			Console::printf("[demo] demo file does not exist: %s", filepath.data());
			return;
		}

		Console::printf("[demo] playing: %s", filepath.data());
		auto reader = std::make_shared<demo_reader>(filepath);
		if (!reader->is_open())
		{
			return;
		}

		{
			std::lock_guard<std::mutex> lock(reader_mutex);
			current_reader = std::move(reader);
			playing_flag = true;
		}

		prevFrameTime = Functions::_Sys_Milliseconds ? Functions::_Sys_Milliseconds() : 0;

		// Drive the match through the normal connection path; the demonware theater
		// server answers "connect demo" and feeds the recorded messages back.
		GameUtil::Cbuf_AddText(LOCAL_CLIENT_0, "connect demo\n");
	}

	static void demo_stop_f()
	{
		stop_playback();
		GameUtil::Cbuf_AddText(LOCAL_CLIENT_0, "disconnect\n");
		Console::printf("[demo] playback stopped");
	}

	static void demo_restart_f()
	{
		auto reader = get_current_demo_reader();
		if (reader)
		{
			reader->restart();
		}
	}

	static void demo_jump_to_f()
	{
		auto reader = get_current_demo_reader();
		CmdArgs* args = GameUtil::getCmdArgs();
		if (!args || !reader)
		{
			return;
		}
		const int nest = args->nesting;
		if (args->argc[nest] < 2)
		{
			return;
		}

		const auto number = std::strtol(args->argv[nest][1], nullptr, 10);
		Console::printf("[demo] jumping to time: %ld", number);
		reader->jump_to(static_cast<int>(number));
	}

	void init()
	{
		demo_paused = reinterpret_cast<dvar_t*>(
			Functions::_Dvar_RegisterBool("demo_paused", false, DVAR_FLAG_NONE));

		cl_get_predicted_player_information_for_server_time_hook.create(
			0x461650_b, &cl_get_predicted_player_information_for_server_time_stub);

		GameUtil::addCommand("demo_play", &demo_play_f);
		GameUtil::addCommand("demo_stop", &demo_stop_f);
		GameUtil::addCommand("demo_restart", &demo_restart_f);
		GameUtil::addCommand("demo_jump_to", &demo_jump_to_f);

		pump_running = true;
		std::thread(&pump_thread).detach();
	}
}
