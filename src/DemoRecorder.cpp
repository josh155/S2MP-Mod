#include "pch.h"
#include "DemoRecorder.hpp"
#include "DemoData.hpp"
#include "DemoByteBuffer.hpp"
#include "DemoPlayback.hpp"

#include "FuncPointers.h"
#include "Console.hpp"
#include "GameUtil.hpp"
#include "Hook.hpp"

#include <optional>
#include <fstream>
#include <filesystem>
#include <windows.h>

// Ported from Airyzz/s1-mod via s2-mod (demo_recorder.cpp), adapted to S2MP-Mod.
//
// Captures the live server message stream into a custom .demo file that the
// playback path replays. The on-disk format is the s1/s2-mod format
// (demo::byte_buffer with data-types disabled).
//
// Verified S2MP-Mod record hooks (IDA MCP against s2x_dump, _b = RVA - 0x1000):
//   CL_Demo_ParseSnapshotMsg                          = 0x4639D0_b (RVA 0x4649D0, in-band)
//     void(int localClientNum, msg_t* msg)
//   CL_Demo_GetNetMsgInfo                             = 0x6C280_b  (RVA 0x6D280, OOB/connectionless)
//     int(int localClientNum, netadr_s* from, msg_t* msg, unsigned int time)
//   CL_SavePredictedPlayerInformationForServerTime    = 0x464580_b (RVA 0x465580, client data)
//     int(clientActive* cl, int serverTime)   [DB mislabels this CG_AddEntityEvent]
namespace demo
{
	namespace
	{
		// clientActive_s offsets confirmed in IDA from CL_SavePredicted... (reads
		// origin from +25704, velocity from +25716, viewAngles from +25728).
		constexpr size_t CA_ORIGIN_OFFSET = 25704;
		constexpr size_t CA_VELOCITY_OFFSET = 25716;
		constexpr size_t CA_VIEWANGLES_OFFSET = 25728;

		int now_ms()
		{
			return Functions::_Sys_Milliseconds ? Functions::_Sys_Milliseconds() : 0;
		}

		std::string get_dvar_string(const std::string& dvar)
		{
			const auto* value = Functions::_Dvar_GetString ? Functions::_Dvar_GetString(dvar.data()) : nullptr;
			return value ? std::string(value) : std::string();
		}

		float read_float_at(const void* base, const size_t offset)
		{
			return *reinterpret_cast<const float*>(reinterpret_cast<const char*>(base) + offset);
		}
	}

	class DemoRecorder
	{
	private:
		std::ofstream stream;

	public:
		bool is_open() const
		{
			return stream.is_open();
		}

		void write_message(int time, msg_t* data)
		{
			if (!stream.is_open() || !data || !data->data || data->cursize <= 0)
			{
				return;
			}

			demo::byte_buffer buffer;
			buffer.set_use_data_types(false);

			const int start = *reinterpret_cast<int*>(data->data);
			if (start == -1)
			{
				time = start;
			}

			buffer.write_int32(time);
			buffer.write_int32(demo_data::DemoPacketType::SERVER_MESSAGE);
			buffer.write_blob(data->data, data->cursize);
			buffer.write_blob(data->splitData ? data->splitData : "", data->splitData ? data->splitSize : 0);

			auto& d = buffer.get_buffer();
			stream.write(d.data(), static_cast<std::streamsize>(d.size()));
			stream.flush();
		}

		void write_client_data(int time, demo_data::demo_client_data_t* data)
		{
			if (!stream.is_open() || !data)
			{
				return;
			}

			demo::byte_buffer buffer;
			buffer.set_use_data_types(false);

			buffer.write_int32(time);
			buffer.write_int32(demo_data::DemoPacketType::CLIENT_DATA);
			buffer.write_blob(reinterpret_cast<char*>(data), static_cast<int>(sizeof(demo_data::demo_client_data_t)));

			auto& d = buffer.get_buffer();
			stream.write(d.data(), static_cast<std::streamsize>(d.size()));
			stream.flush();
		}

		void init()
		{
			std::filesystem::create_directory("demos");

			auto map = get_dvar_string("ui_mapname");
			auto type = get_dvar_string("g_gametype");
			if (map.empty()) map = "unknown";
			if (type.empty()) type = "war";

			SYSTEMTIME st{};
			GetLocalTime(&st);

			char path[MAX_PATH]{};
			_snprintf_s(path, _TRUNCATE, "demos/%s_%s_%02u_%02u_%04u_%02u_%02u.demo",
				type.c_str(), map.c_str(), st.wMonth, st.wDay, st.wYear, st.wHour, st.wMinute);

			stream = std::ofstream(path, std::ios::binary | std::ofstream::out);
			if (!stream.is_open())
			{
				Console::printf("[demo] failed to open recording file: %s", path);
				return;
			}

			demo::byte_buffer buffer;
			buffer.set_use_data_types(false);
			buffer.write_blob(map);
			buffer.write_blob(type);

			auto& d = buffer.get_buffer();
			stream.write(d.data(), static_cast<std::streamsize>(d.size()));
			stream.flush();

			Console::printf("[demo] recording -> %s (map=%s mode=%s)", path, map.c_str(), type.c_str());
		}

		void close()
		{
			if (stream.is_open())
			{
				stream.close();
			}
		}
	};

	std::optional<DemoRecorder> recorder;

	utils::hook::detour cl_parseservermessage_hook;
	utils::hook::detour cl_connectionlesspacket_hook;
	utils::hook::detour cl_save_predicted_player_information_for_server_time_hook;

	// s2-mod uses mp::virtualLobby_Loaded @ RVA 0x1BD36F8 -> 0x1BD26F8_b. The s2x_dump
	// DB labels that address cl_demoKillServerFlag, but every s2-mod address has
	// verified correct by behavior, so we trust it here (non-critical guard).
	// TODO: confirm against the live build.
	bool virtual_lobby_loaded()
	{
		return *reinterpret_cast<int*>(0x1BD26F8_b) != 0;
	}

	void begin_recording()
	{
		Console::printf("----- Beginning demo recording -----");
		Console::printf("----- Map:  %s -----", get_dvar_string("mapname").data());
		Console::printf("----- Mode: %s -----", get_dvar_string("g_gametype").data());
		recorder = DemoRecorder();
		recorder->init();
		if (!recorder->is_open())
		{
			recorder = std::nullopt;
		}
	}

	void stop_recording()
	{
		if (recorder)
		{
			recorder->close();
			recorder = std::nullopt;
			Console::printf("[demo] recording stopped");
		}
	}

	// CL_Demo_ParseSnapshotMsg (0x4639D0_b) - per in-band server message.
	void cl_parseservermessage_stub(int localClientNum, msg_t* message)
	{
		cl_parseservermessage_hook.invoke<void>(localClientNum, message);

		if (demo_playback::is_playing() || !message || message->overflowed)
		{
			return;
		}

		if (recorder)
		{
			recorder->write_message(now_ms(), message);
		}
	}

	// CL_Demo_GetNetMsgInfo (0x6C280_b) - per out-of-band (connectionless) packet.
	int cl_connectionlesspacket_stub(int localClientNum, netadr_s* from, msg_t* message, unsigned int time)
	{
		std::string data;
		if (message && message->data && message->cursize > 0)
		{
			data.assign(message->data, message->cursize);
		}

		const auto result = cl_connectionlesspacket_hook.invoke<int>(localClientNum, from, message, time);

		if (demo_playback::is_playing())
		{
			return result;
		}

		// connectResponse marks the start of a fresh connection -> begin a new recording
		// (but not while sitting in the virtual lobby / frontend).
		if (data.starts_with("\xff\xff\xff\xff" "connectResponse"))
		{
			if (!virtual_lobby_loaded())
			{
				begin_recording();
			}
		}

		if (!message || message->overflowed)
		{
			return result;
		}

		// We don't need to record this.
		if (data.starts_with("\xff\xff\xff\xff" "syncDataResponse"))
		{
			return result;
		}

		if (recorder)
		{
			recorder->write_message(now_ms(), message);
		}

		return result;
	}

	// CL_SavePredictedPlayerInformationForServerTime (0x464580_b) - snapshot of the
	// local player's predicted state, captured for the playback view.
	int cl_save_predicted_player_information_for_server_time_stub(void* clientActive, int serverTime)
	{
		const auto result = cl_save_predicted_player_information_for_server_time_hook.invoke<int>(clientActive, serverTime);

		if (recorder && clientActive)
		{
			demo_data::demo_client_data_t data{};
			data.predictedDataServerTime = serverTime;

			data.origin[0] = read_float_at(clientActive, CA_ORIGIN_OFFSET + 0);
			data.origin[1] = read_float_at(clientActive, CA_ORIGIN_OFFSET + 4);
			data.origin[2] = read_float_at(clientActive, CA_ORIGIN_OFFSET + 8);

			data.velocity[0] = read_float_at(clientActive, CA_VELOCITY_OFFSET + 0);
			data.velocity[1] = read_float_at(clientActive, CA_VELOCITY_OFFSET + 4);
			data.velocity[2] = read_float_at(clientActive, CA_VELOCITY_OFFSET + 8);

			data.viewAngles[0] = read_float_at(clientActive, CA_VIEWANGLES_OFFSET + 0);
			data.viewAngles[1] = read_float_at(clientActive, CA_VIEWANGLES_OFFSET + 4);
			data.viewAngles[2] = read_float_at(clientActive, CA_VIEWANGLES_OFFSET + 8);

			// bobCycle / movementDir offsets not yet confirmed -> milestone 2.
			data.bobCycle = 0;
			data.movementDir = 0;

			recorder->write_client_data(now_ms(), &data);
		}

		return result;
	}

	static void demo_record_f()
	{
		if (recorder)
		{
			Console::printf("[demo] already recording");
			return;
		}
		begin_recording();
	}

	static void demo_record_stop_f()
	{
		stop_recording();
	}

	void init()
	{
		cl_parseservermessage_hook.create(0x4639D0_b, &cl_parseservermessage_stub);
		cl_connectionlesspacket_hook.create(0x6C280_b, &cl_connectionlesspacket_stub);
		cl_save_predicted_player_information_for_server_time_hook.create(
			0x464580_b, &cl_save_predicted_player_information_for_server_time_stub);

		// Manual record controls (recording also auto-starts on connectResponse).
		GameUtil::addCommand("demo_record", &demo_record_f);
		GameUtil::addCommand("demo_record_stop", &demo_record_stop_f);
	}
}
