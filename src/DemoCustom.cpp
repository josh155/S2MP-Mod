#include "pch.h"
#include "DemoCustom.hpp"
#include "FuncPointers.h"
#include "Console.hpp"
#include "GameUtil.hpp"
#include "Hook.hpp"

#include <intrin.h>
#include <cstdio>
#include <filesystem>
#pragma intrinsic(_ReturnAddress)

// Clean rebuild of the working V055 custom demo system. See DemoCustom.hpp.
// Hook/data addresses are S2MP-Mod _b offsets (= V055 s2_mp64_ship RVA - 0x1000).
//   CL_Demo_ParseGamestateMsg   0x462B00 -> 0x461B00_b
//   CL_Demo_ParseSnapshotMsg    0x4649D0 -> 0x4639D0_b
//   CL_Demo_DispatchSnapshotMsg 0x4636E0 -> 0x4626E0_b
//   CL_Demo_IsPlaying           0x910400 -> 0x90F400_b
//   Com_Error_va                0x90750  -> 0x8F750_b
//   CL_StartMapLoadConnection   0x6DC350 -> 0x6DB350_b
//   cl_clientConnection[0]      0x1BAF450-> 0x1BAE450_b  (stride 0x7B8, connectState +0x94)
//   virtualLobby active flag    -> 0x1BD26F8_b
namespace demo_custom
{
	namespace
	{
		struct demo_msg_t
		{
			int allowoverflow;  // 0x00
			int overflowed;     // 0x04
			char* data;         // 0x08
			char* splitdata;    // 0x10
			int maxsize;        // 0x18
			int cursize;        // 0x1C
			int readcount;      // 0x20
			int bit;            // 0x24
			int lastEntityRef;  // 0x28
			int flags;          // 0x2C
		};
		static_assert(sizeof(demo_msg_t) == 0x30, "demo_msg_t");

		enum : unsigned { W2DR_MAGIC = 0x52443257u, W2DR_VERSION = 8 };
		enum recType : unsigned { REC_MAPINFO = 1, REC_GAMESTATE = 3, REC_SNAPSHOT = 4, REC_DISPATCH = 5, REC_CLIENTDATA = 6, REC_USERCMD = 7, REC_ARCHIVE = 8 };
		constexpr unsigned USERCMD_SIZE = 128; // usercmd_s (CL_CreateNewCommands strides 128)
		constexpr unsigned ARCHIVE_SIZE = 128; // CL_Demo_UpdateStatsRing builds a 128-byte stats/view blob

#pragma pack(push, 1)
		struct W2DRHeader { unsigned magic, version, headerSize, flags; char map[128]; char mode[64]; };
		struct W2DRRecord { unsigned type, client, state, size, readByte, readBit, flags, seq, lastEntityRef, time; };
		// recorded local-player predicted state (fixes view origin/angles + viewmodel)
		struct client_data_t { int serverTime; float origin[3]; float velocity[3]; float viewAngles[3]; int bobCycle; int movementDir; };
#pragma pack(pop)

		// clientActive offsets (verified): origin +25704, velocity +25716, viewAngles +25728.
		// playerState offsets (verified): origin +132, velocity +144.
		constexpr size_t CA_ORIGIN = 25704, CA_VELOCITY = 25716, CA_VIEWANGLES = 25728;
		constexpr size_t PS_ORIGIN = 132, PS_VELOCITY = 144;

		// hooks
		utils::hook::detour g_gamestateHook, g_snapshotHook, g_dispatchHook, g_isPlayingHook, g_comErrorHook;
		utils::hook::detour g_initClientHook;
		utils::hook::detour g_runFrameHook;
		utils::hook::detour g_execMenuHook;
		utils::hook::detour g_savePredictedHook;
		utils::hook::detour g_getPredictedHook;
		utils::hook::detour g_createCmdHook;
		utils::hook::detour g_updateStatsHook;

		// recorded predicted-player-state ring, indexed by serverTime & 255
		client_data_t g_clientFrames[256] = {};

		// recorded local usercmd ring (drives view angles + buttons + weapon on replay)
		struct cmd_rec { int serverTime; unsigned char cmd[USERCMD_SIZE]; };
		cmd_rec g_cmdFrames[256] = {};

		// recorded 128-byte view/stats archive blob (CL_Demo_UpdateStatsRing) - the
		// authoritative view state during rendering; the live build is blank in playback.
		struct archive_rec { int serverTime; unsigned char blob[ARCHIVE_SIZE]; };
		archive_rec g_archiveFrames[256] = {};

		// pacing: feed pairs at their recorded wall-clock spacing
		int g_pbWallStart = 0;
		unsigned g_pbFirstRecTime = 0;
		bool g_pbHaveFirstTime = false;
		bool g_pendValid = false;
		W2DRRecord g_pendSnapR{}, g_pendDispR{};
		void* g_pendSnapP = nullptr;
		void* g_pendDispP = nullptr;

		// recording state
		bool g_recording = false;
		bool g_seenUseful = false;
		FILE* g_recFile = nullptr;
		char g_curMap[128] = {};
		char g_curMode[64] = {};

		// playback state
		bool g_playing = false;
		bool g_armed = false;
		bool g_driving = false;
		bool g_forceIsPlaying = false;
		FILE* g_pbFile = nullptr;
		int g_pbNextTick = 0;
		int g_pbArmTick = 0;
		unsigned g_naturalSnaps = 0;
		int g_savedMode = -1;
		bool g_savedModeValid = false;

		// dispatch-override (paired snapshot+dispatch replay)
		bool g_insideOuterSnapshot = false;
		bool g_overrideReady = false;
		demo_msg_t g_pendingDispatch{};
		demo_msg_t g_pendingDestroy{};

		constexpr int PB_PUMP_INTERVAL_MS = 90;
		constexpr int PB_ARM_DELAY_MS = 600;        // let the engine settle before pumping
		constexpr unsigned PB_MIN_NATURAL_SNAPS = 8; // and see this many demo-frame snapshots first

		uintptr_t g_base = 0;
		uintptr_t base()
		{
			if (!g_base) g_base = reinterpret_cast<uintptr_t>(GetModuleHandleA(nullptr));
			return g_base;
		}
		uintptr_t ptr_to_rva(const void* p)
		{
			const auto a = reinterpret_cast<uintptr_t>(p);
			const auto b = base();
			return (b && a >= b) ? (a - b) : a;
		}
		int sys_ms() { return Functions::_Sys_Milliseconds ? Functions::_Sys_Milliseconds() : 0; }

		// cl_serverTime (0xC5EA44_b) - the smooth server tick the engine interpolates by.
		// Used as the record timestamp so playback paces to server time, not jittery
		// packet-arrival wall-clock.
		int server_time()
		{
			__try { return *reinterpret_cast<int*>(0xC5EA44_b); }
			__except (EXCEPTION_EXECUTE_HANDLER) { return 0; }
		}

		bool is_gamestate_isplaying_site(uintptr_t rva); // defined below

		// ---- POD memory helpers (safe under __try) ----
		int read_state(int client)
		{
			if (client < 0 || client >= 3) return -1;
			__try { return *reinterpret_cast<int*>(0x1BAE450_b + static_cast<uintptr_t>(client) * 0x7B8 + 0x94); }
			__except (EXCEPTION_EXECUTE_HANDLER) { return -1; }
		}
		bool is_virtual_lobby()
		{
			__try { return *reinterpret_cast<unsigned char*>(0x1BD26F8_b) != 0; }
			__except (EXCEPTION_EXECUTE_HANDLER) { return false; }
		}
		bool read_msg(void* msg, void*& data, unsigned& size, unsigned& rb, unsigned& bit, unsigned& flags, unsigned& lastEnt)
		{
			data = nullptr; size = rb = bit = flags = lastEnt = 0;
			if (!msg) return false;
			__try
			{
				auto* m = reinterpret_cast<demo_msg_t*>(msg);
				data = m->data;
				size = static_cast<unsigned>(m->cursize);
				rb = static_cast<unsigned>(m->readcount);
				bit = static_cast<unsigned>(m->bit);
				flags = static_cast<unsigned>(m->flags);
				lastEnt = static_cast<unsigned>(m->lastEntityRef);
				return data && size && size < (16u * 1024u * 1024u);
			}
			__except (EXCEPTION_EXECUTE_HANDLER) { return false; }
		}
		bool fmt_is_398(const char* fmt)
		{
			__try { return fmt && fmt[0] == '3' && fmt[1] == '9' && fmt[2] == '8' && fmt[3] == 0; }
			__except (EXCEPTION_EXECUTE_HANDLER) { return false; }
		}

		// TempMemory stack positions (main thread off_E098A8 @ 0xE088A8_b, render
		// thread off_E09890 @ 0xE08890_b). If a parser AVs mid-way, it skips its
		// TempMemory_Free, leaking its 0x20000 block until the allocator fails
		// ("Memory Error 16 255"). We snapshot these positions and, on AV, rewind them
		// to reclaim exactly what the failed call allocated.
		struct temp_scope { void* r; void* m; };
		temp_scope temp_save()
		{
			temp_scope s{ nullptr, nullptr };
			__try { s.r = *reinterpret_cast<void**>(0xE08890_b); s.m = *reinterpret_cast<void**>(0xE088A8_b); }
			__except (EXCEPTION_EXECUTE_HANDLER) {}
			return s;
		}
		void temp_restore(temp_scope s)
		{
			__try { *reinterpret_cast<void**>(0xE08890_b) = s.r; *reinterpret_cast<void**>(0xE088A8_b) = s.m; }
			__except (EXCEPTION_EXECUTE_HANDLER) {}
		}

		// captured fault RVAs (which instruction the replay AVs at) for diagnosis
		unsigned g_gsFaultRva = 0;
		unsigned g_snapFaultRva = 0;
		unsigned fault_rva(EXCEPTION_POINTERS* ep)
		{
			return ep ? static_cast<unsigned>(reinterpret_cast<uintptr_t>(ep->ExceptionRecord->ExceptionAddress) - base()) : 0;
		}

		// ---- POD parser invocations (AV-safe AND temp-memory-leak-safe) ----
		bool invoke_gamestate(int client, demo_msg_t* m)
		{
			temp_scope ts = temp_save();
			__try { g_gamestateHook.invoke<void>(client, m); return true; }
			__except (g_gsFaultRva = fault_rva(GetExceptionInformation()), EXCEPTION_EXECUTE_HANDLER) { temp_restore(ts); return false; }
		}
		bool invoke_snapshot(int client, demo_msg_t* m)
		{
			temp_scope ts = temp_save();
			__try { g_snapshotHook.invoke<void>(client, m); return true; }
			__except (g_snapFaultRva = fault_rva(GetExceptionInformation()), EXCEPTION_EXECUTE_HANDLER) { temp_restore(ts); return false; }
		}
		bool invoke_dispatch(int client, demo_msg_t* m, demo_msg_t* destroy)
		{
			temp_scope ts = temp_save();
			__try { g_dispatchHook.invoke<__int64>(client, m, destroy); return true; }
			__except (EXCEPTION_EXECUTE_HANDLER) { temp_restore(ts); return false; }
		}
		bool run_map_route(char* map)
		{
			using route_t = __int64(__fastcall*)(char*, __int64, unsigned, unsigned);
			__try { reinterpret_cast<route_t>(0x6DB350_b)(map, 0, 0, 0); return true; }
			__except (EXCEPTION_EXECUTE_HANDLER) { return false; }
		}

		// cl_demoClients pointer (RVA 0x1BD3D00 -> 0x1BD2D00_b); per-client stride 0x75D60.
		unsigned char* demo_client_base(int client)
		{
			if (client < 0 || client >= 3) return nullptr;
			__try
			{
				auto* arr = *reinterpret_cast<unsigned char**>(0x1BD2D00_b);
				return arr ? arr + static_cast<uintptr_t>(client) * 0x75D60 : nullptr;
			}
			__except (EXCEPTION_EXECUTE_HANDLER) { return nullptr; }
		}

		// Seed the demo server-command stream config (dc+0x54830 +0x10..+0x20) to
		// {2,0,0,2,244}. Without this the enqueue (sub_66E290) returns 0x90000002 and
		// the client EXE_DISCONNECTs during the gamestate's server-command parse.
		void patch_stream_config(int client)
		{
			__try
			{
				auto* dc = demo_client_base(client);
				if (!dc) return;
				auto* s = dc + 0x54830;
				*reinterpret_cast<unsigned*>(s + 0x10) = 2;
				*reinterpret_cast<unsigned*>(s + 0x14) = 0;
				*reinterpret_cast<unsigned*>(s + 0x18) = 0;
				*reinterpret_cast<unsigned*>(s + 0x1C) = 2;
				*reinterpret_cast<unsigned*>(s + 0x20) = 244;
			}
			__except (EXCEPTION_EXECUTE_HANDLER) {}
		}

		// CL_Demo_ExecMenuPlayDemo (tail-called by the gamestate parser) throws "432"
		// unless dc+0x40268 == 0x1D. Seed it so the gamestate parse completes instead
		// of AV'ing at the tail (which leaves baselines unfinalised).
		void patch_exec_menu_marker(int client)
		{
			__try { auto* dc = demo_client_base(client); if (dc) *reinterpret_cast<unsigned*>(dc + 0x40268) = 0x1D; }
			__except (EXCEPTION_EXECUTE_HANDLER) {}
		}

		// demoClient.mode (dc+0x10) == 2 puts the engine into demo-playback mode, so
		// CL_Demo_IsPlaying returns true broadly and the demo frame loop runs (which
		// is what generates the natural snapshot calls that drive playback).
		void set_demo_client_mode(int client, int mode)
		{
			__try
			{
				auto* dc = demo_client_base(client);
				if (!dc) return;
				if (!g_savedModeValid) { g_savedMode = *reinterpret_cast<int*>(dc + 0x10); g_savedModeValid = true; }
				*reinterpret_cast<int*>(dc + 0x10) = mode;
			}
			__except (EXCEPTION_EXECUTE_HANDLER) {}
		}
		void restore_demo_client_mode(int client)
		{
			if (!g_savedModeValid) return;
			__try { auto* dc = demo_client_base(client); if (dc) *reinterpret_cast<int*>(dc + 0x10) = g_savedMode; }
			__except (EXCEPTION_EXECUTE_HANDLER) {}
			g_savedModeValid = false;
		}

		// CL_InitClientFromGamestateMsg (0x6F830_b): keep the stream config seeded
		// across the native gamestate init that runs inside the gamestate parser.
		__int64 initclient_hook(int client, __int64 a2, __int64 a3)
		{
			if (g_playing || g_armed) { patch_stream_config(client); patch_exec_menu_marker(client); }
			__int64 ret = 0;
			__try { ret = g_initClientHook.invoke<__int64>(client, a2, a3); }
			__except (EXCEPTION_EXECUTE_HANDLER) {}
			if (g_playing || g_armed) { patch_stream_config(client); patch_exec_menu_marker(client); }
			return ret;
		}

		// ---- map/mode extraction from a gamestate payload (POD scan) ----
		bool clean_token_char(char c)
		{
			return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_' || c == '-';
		}
		bool token_at(const unsigned char* d, unsigned size, unsigned off, char* out, unsigned outSize)
		{
			unsigned len = 0;
			while (off + len < size && len + 1 < outSize)
			{
				const char c = static_cast<char>(d[off + len]);
				if (!c) { if (!len) return false; out[len] = 0; return true; }
				if (!clean_token_char(c)) return false;
				out[len++] = c;
			}
			return false;
		}
		bool starts_with_i(const char* s, const char* p)
		{
			for (; *p; ++s, ++p)
			{
				char a = *s, b = *p;
				if (a >= 'A' && a <= 'Z') a += 32;
				if (b >= 'A' && b <= 'Z') b += 32;
				if (a != b) return false;
			}
			return true;
		}
		bool is_hub_map(const char* m) { return m && starts_with_i(m, "mp_hub_"); }
		void extract_map_mode(const unsigned char* d, unsigned size, char* mapOut, char* modeOut)
		{
			mapOut[0] = 0; modeOut[0] = 0;
			if (!d || !size) return;
			char tok[128];
			for (unsigned i = 0; i < size; ++i)
			{
				if (!token_at(d, size, i, tok, sizeof(tok))) continue;
				if (!mapOut[0] && starts_with_i(tok, "mp_")) { strncpy_s(mapOut, 128, tok, _TRUNCATE); }
				else if (!modeOut[0] && (starts_with_i(tok, "war") || starts_with_i(tok, "dm") ||
					starts_with_i(tok, "dom") || starts_with_i(tok, "sd") || starts_with_i(tok, "ctf") ||
					starts_with_i(tok, "hp") || starts_with_i(tok, "conf") || starts_with_i(tok, "gun")))
				{
					strncpy_s(modeOut, 64, tok, _TRUNCATE);
				}
				if (mapOut[0] && modeOut[0]) break;
			}
			if (mapOut[0] && is_hub_map(mapOut) && !modeOut[0]) strncpy_s(modeOut, 64, "hub", _TRUNCATE);
		}

		// ---- recording ----
		void write_record(unsigned type, int client, int state, const void* data, unsigned size,
			unsigned rb, unsigned bit, unsigned flags, unsigned seq, unsigned lastEnt)
		{
			if (!g_recFile || !data || !size) return;
			// Timestamp by cl_serverTime (smooth server tick the engine interpolates by),
			// not packet-arrival wall-clock, so playback pacing has no network jitter.
			W2DRRecord r{ type, static_cast<unsigned>(client), static_cast<unsigned>(state), size, rb, bit, flags, seq, lastEnt, static_cast<unsigned>(server_time()) };
			fwrite(&r, 1, sizeof(r), g_recFile);
			fwrite(data, 1, size, g_recFile);
			fflush(g_recFile);
		}

		void stop_recording(const char* reason)
		{
			if (!g_recording) return;
			if (g_recFile) { fclose(g_recFile); g_recFile = nullptr; }
			g_recording = false;
			g_seenUseful = false;
			Console::printf("[demo] recording stopped (%s)", reason ? reason : "");
		}

		void start_recording()
		{
			if (g_recording) return;
			std::error_code ec;
			std::filesystem::create_directory("demos", ec);

			SYSTEMTIME st{}; GetLocalTime(&st);
			char path[MAX_PATH];
			_snprintf_s(path, _TRUNCATE, "demos/%s_%s_%02u%02u%04u_%02u%02u%02u.w2dr",
				g_curMode[0] ? g_curMode : "war", g_curMap[0] ? g_curMap : "unknown",
				st.wMonth, st.wDay, st.wYear, st.wHour, st.wMinute, st.wSecond);

			fopen_s(&g_recFile, path, "wb");
			if (!g_recFile) { Console::printf("[demo] failed to open %s", path); return; }

			W2DRHeader h{ W2DR_MAGIC, W2DR_VERSION, sizeof(W2DRHeader), 0, {}, {} };
			strncpy_s(h.map, sizeof(h.map), g_curMap[0] ? g_curMap : "unknown", _TRUNCATE);
			strncpy_s(h.mode, sizeof(h.mode), g_curMode[0] ? g_curMode : "war", _TRUNCATE);
			fwrite(&h, 1, sizeof(h), g_recFile);
			fflush(g_recFile);

			g_recording = true;
			g_seenUseful = true;
			Console::printf("[demo] recording -> %s (map=%s mode=%s)", path, h.map, h.mode);
		}

		// ---- playback ----
		void build_msg(demo_msg_t* m, void* payload, const W2DRRecord& r)
		{
			memset(m, 0, sizeof(*m));
			m->data = static_cast<char*>(payload);
			m->maxsize = static_cast<int>(r.size);
			m->cursize = static_cast<int>(r.size);
			m->readcount = static_cast<int>(r.readByte);
			m->bit = static_cast<int>(r.readBit);
			m->lastEntityRef = static_cast<int>(r.lastEntityRef);
			m->flags = static_cast<int>(r.flags);
		}
		bool read_record(FILE* f, W2DRRecord& r, void*& payload)
		{
			payload = nullptr;
			if (!f || fread(&r, 1, sizeof(r), f) != sizeof(r)) return false;
			if (r.size > (16u * 1024u * 1024u)) return false;
			payload = malloc(r.size ? r.size : 1);
			if (!payload) return false;
			if (r.size && fread(payload, 1, r.size, f) != r.size) { free(payload); payload = nullptr; return false; }
			return true;
		}
		void close_playback(const char* reason)
		{
			if (g_pbFile) { fclose(g_pbFile); g_pbFile = nullptr; }
			if (g_pendSnapP) { free(g_pendSnapP); g_pendSnapP = nullptr; }
			if (g_pendDispP) { free(g_pendDispP); g_pendDispP = nullptr; }
			g_pendValid = false;
			if (g_playing || g_armed) Console::printf("[demo] playback stopped (%s)", reason ? reason : "");
			restore_demo_client_mode(0);
			g_playing = false;
			g_armed = false;
			g_driving = false;
		}

		// Feed the first recorded gamestate after the map has loaded.
		bool feed_gamestate()
		{
			for (int i = 0; i < 512; ++i)
			{
				W2DRRecord r{}; void* payload = nullptr;
				if (!read_record(g_pbFile, r, payload)) return false;
				if (r.type != REC_GAMESTATE) { free(payload); continue; }

				demo_msg_t m{}; build_msg(&m, payload, r);
				patch_stream_config(static_cast<int>(r.client));
				patch_exec_menu_marker(static_cast<int>(r.client));
				g_driving = true; g_forceIsPlaying = true;
				const bool ok = invoke_gamestate(static_cast<int>(r.client), &m);
				g_forceIsPlaying = false; g_driving = false;
				free(payload);

				const int st = read_state(0);
				Console::printf("[demo] fed gamestate (ok=%d state=%d gsFaultRva=0x%X)", ok ? 1 : 0, st, g_gsFaultRva);
				// The post-init tail can AV after the client has already advanced; treat
				// state>=9 as success (matches V055).
				return ok || st >= 9;
			}
			return false;
		}

		unsigned g_pbExceptions = 0;
		unsigned g_pbApplied = 0;

		// Store an auxiliary (non snapshot/dispatch) record into its ring. Returns true
		// if it consumed the record.
		bool store_aux_record(const W2DRRecord& r, void* payload)
		{
			if (r.type == REC_CLIENTDATA && r.size >= sizeof(client_data_t))
			{
				auto* d = reinterpret_cast<client_data_t*>(payload);
				g_clientFrames[d->serverTime & 255] = *d;
				return true;
			}
			if (r.type == REC_USERCMD && r.size >= sizeof(cmd_rec))
			{
				auto* c = reinterpret_cast<cmd_rec*>(payload);
				g_cmdFrames[c->serverTime & 255] = *c;
				return true;
			}
			if (r.type == REC_ARCHIVE && r.size >= sizeof(archive_rec))
			{
				auto* ar = reinterpret_cast<archive_rec*>(payload);
				g_archiveFrames[ar->serverTime & 255] = *ar;
				return true;
			}
			return false;
		}

		// Read records (populating the predicted-state ring from REC_CLIENTDATA) until a
		// snapshot+dispatch pair is buffered in g_pend*. Returns false at eof. Does NOT
		// feed yet - pacing decides when. (Reading ahead also primes the client-data ring
		// so the get-predicted hook has the data when the engine renders that frame.)
		bool load_next_pair()
		{
			if (g_pendValid || !g_pbFile) return g_pendValid;

			W2DRRecord snapR{}; void* snapP = nullptr;
			for (;;)
			{
				if (!read_record(g_pbFile, snapR, snapP)) { close_playback("eof"); return false; }
				if (store_aux_record(snapR, snapP)) { free(snapP); continue; }
				if (snapR.type == REC_SNAPSHOT) break;
				free(snapP); // skip gamestate/other
			}

			W2DRRecord dispR{}; void* dispP = nullptr;
			for (;;)
			{
				if (!read_record(g_pbFile, dispR, dispP)) { free(snapP); close_playback("missing dispatch"); return false; }
				if (store_aux_record(dispR, dispP)) { free(dispP); continue; }
				break;
			}
			if (dispR.type != REC_DISPATCH)
			{
				free(snapP); free(dispP); close_playback("pair mismatch"); return false;
			}

			g_pendSnapR = snapR; g_pendDispR = dispR; g_pendSnapP = snapP; g_pendDispP = dispP;
			g_pendValid = true;
			return true;
		}

		// Feed the buffered pair. A replay AV is counted+reclaimed (temp scoping) and we
		// keep going. CS_ACTIVE (state 10) takes the direct-dispatch path; before that,
		// the outer-snapshot-with-dispatch-override path.
		void feed_pending()
		{
			if (!g_pendValid) return;
			const int state = read_state(static_cast<int>(g_pendSnapR.client));
			patch_stream_config(static_cast<int>(g_pendSnapR.client));
			g_driving = true;
			bool ok;
			if (state >= 10)
			{
				demo_msg_t dm{}, destroy{}; build_msg(&dm, g_pendDispP, g_pendDispR);
				ok = invoke_dispatch(static_cast<int>(g_pendDispR.client), &dm, &destroy);
			}
			else
			{
				demo_msg_t sm{}; build_msg(&sm, g_pendSnapP, g_pendSnapR);
				build_msg(&g_pendingDispatch, g_pendDispP, g_pendDispR);
				memset(&g_pendingDestroy, 0, sizeof(g_pendingDestroy));
				g_overrideReady = true; g_insideOuterSnapshot = true;
				ok = invoke_snapshot(static_cast<int>(g_pendSnapR.client), &sm);
				g_insideOuterSnapshot = false; g_overrideReady = false;
			}
			g_driving = false;
			free(g_pendSnapP); free(g_pendDispP);
			g_pendSnapP = g_pendDispP = nullptr; g_pendValid = false;
			if (ok) ++g_pbApplied; else ++g_pbExceptions;
		}

		// ---- hooks ----
		void gamestate_hook(int client, void* msg)
		{
			void* data; unsigned size, rb, bit, flags, lastEnt;
			const bool ok = read_msg(msg, data, size, rb, bit, flags, lastEnt);
			const int state = read_state(client);

			char map[128] = {}, mode[64] = {};
			if (ok) extract_map_mode(reinterpret_cast<unsigned char*>(data) + (rb < size ? rb : 0), size - (rb < size ? rb : 0), map, mode);

			const bool frontendOrHub = is_hub_map(map) || is_virtual_lobby() || (state == 0 && !map[0]);

			if (!g_playing && ok && !frontendOrHub && map[0])
			{
				if (map[0]) strncpy_s(g_curMap, sizeof(g_curMap), map, _TRUNCATE);
				if (mode[0]) strncpy_s(g_curMode, sizeof(g_curMode), mode, _TRUNCATE);
				if (!g_recording) start_recording(); // AUTO record on a real match
				if (g_recording) write_record(REC_GAMESTATE, client, state, data, size, rb, bit, flags, 0, lastEnt);
			}
			else if (g_recording && frontendOrHub)
			{
				stop_recording("returned to lobby");
			}

			g_gamestateHook.invoke<void>(client, msg);
		}

		void snapshot_hook(int client, void* msg)
		{
			void* data; unsigned size, rb, bit, flags, lastEnt;
			const bool ok = read_msg(msg, data, size, rb, bit, flags, lastEnt);

			if (!g_playing && !g_driving && g_recording && g_seenUseful && ok)
			{
				unsigned seq = 0;
				if (size >= 4) { __try { seq = *reinterpret_cast<unsigned*>(data); } __except (EXCEPTION_EXECUTE_HANDLER) {} }
				write_record(REC_SNAPSHOT, client, read_state(client), data, size, rb, bit, flags, seq, lastEnt);
			}

			g_snapshotHook.invoke<void>(client, msg);
			// (playback is paced one pair/frame by the CL_Demo_RunFrame hook)
		}

		__int64 dispatch_hook(int client, void* msg, void* destroy)
		{
			// Override the snapshot parser's internal dispatch with the recorded payload.
			if (g_insideOuterSnapshot && g_overrideReady)
			{
				return g_dispatchHook.invoke<__int64>(client, &g_pendingDispatch, &g_pendingDestroy);
			}

			if (!g_playing && !g_driving && g_recording && g_seenUseful)
			{
				void* data; unsigned size, rb, bit, flags, lastEnt;
				if (read_msg(msg, data, size, rb, bit, flags, lastEnt))
				{
					unsigned seq = 0;
					if (rb < size) { __try { seq = reinterpret_cast<unsigned char*>(data)[rb]; } __except (EXCEPTION_EXECUTE_HANDLER) {} }
					write_record(REC_DISPATCH, client, read_state(client), data, size, rb, bit, flags, seq, lastEnt);
				}
			}

			return g_dispatchHook.invoke<__int64>(client, msg, destroy);
		}

		// CL_Demo_ExecMenuPlayDemo (0x91D310_b): the gamestate parser tail-calls this
		// native menu-play-demo routine, which dereferences CL_Demo_GetPlayback() and
		// the native playback context we don't set up -> AV at 0x91E320. We don't need
		// it for custom playback, so no-op it while playing.
		void* execmenu_hook()
		{
			if (g_playing || g_armed) return nullptr;
			void* r = nullptr;
			__try { r = g_execMenuHook.invoke<void*>(); }
			__except (EXCEPTION_EXECUTE_HANDLER) {}
			return r;
		}

		// CL_Demo_RunFrame (0x85D30_b): the engine's per-frame demo driver. We feed
		// exactly ONE recorded snapshot+dispatch pair per frame here, so the engine's
		// frame-end temp-memory free runs between feeds (otherwise TempMemory overflows
		// -> "Memory Error 16 255").
		__int64 runframe_hook(unsigned int client)
		{
			__int64 ret = 0;
			__try { ret = g_runFrameHook.invoke<__int64>(client); }
			__except (EXCEPTION_EXECUTE_HANDLER) {}

			if (g_armed && !g_driving && client == 0)
			{
				if (!g_pendValid) load_next_pair();
				if (g_pendValid)
				{
					if (!g_pbHaveFirstTime) { g_pbHaveFirstTime = true; g_pbFirstRecTime = g_pendSnapR.time; g_pbWallStart = sys_ms(); }
					// feed at most one pair per frame, when its recorded time is due
					if (sys_ms() - g_pbWallStart >= static_cast<int>(g_pendSnapR.time - g_pbFirstRecTime))
					{
						static unsigned pumpN = 0;
						feed_pending();
						if ((++pumpN % 60) == 1)
							Console::printf("[demo] pump #%u state=%d applied=%u av=%u snapFaultRva=0x%X", pumpN, read_state(0), g_pbApplied, g_pbExceptions, g_snapFaultRva);
					}
				}
			}
			return ret;
		}

		// CL_SavePredictedPlayerInformationForServerTime (0x464580_b): record the local
		// player's predicted origin/velocity/viewangles per serverTime.
		int save_predicted_hook(void* clientActive, int serverTime)
		{
			int ret = 0;
			__try { ret = g_savePredictedHook.invoke<int>(clientActive, serverTime); }
			__except (EXCEPTION_EXECUTE_HANDLER) {}

			if (!g_playing && g_recording && g_seenUseful && clientActive)
			{
				client_data_t d{};
				d.serverTime = serverTime;
				__try
				{
					const char* ca = reinterpret_cast<const char*>(clientActive);
					memcpy(d.origin, ca + CA_ORIGIN, sizeof(d.origin));
					memcpy(d.velocity, ca + CA_VELOCITY, sizeof(d.velocity));
					memcpy(d.viewAngles, ca + CA_VIEWANGLES, sizeof(d.viewAngles));
				}
				__except (EXCEPTION_EXECUTE_HANDLER) {}
				write_record(REC_CLIENTDATA, 0, read_state(0), &d, sizeof(d), 0, 0, 0, static_cast<unsigned>(serverTime), 0);
			}
			return ret;
		}

		// CL_GetPredictedPlayerInformationForServerTime (0x461650_b): during playback,
		// overwrite the predicted origin/velocity with the recorded values so the view
		// follows the recording.
		__int64 get_predicted_hook(void* clientActive, int serverTime, void* playerState)
		{
			__int64 ret = 0;
			__try { ret = g_getPredictedHook.invoke<__int64>(clientActive, serverTime, playerState); }
			__except (EXCEPTION_EXECUTE_HANDLER) {}

			if (g_playing && playerState)
			{
				__try
				{
					const client_data_t& d = g_clientFrames[serverTime & 255];
					if (d.serverTime == serverTime)
					{
						char* ps = reinterpret_cast<char*>(playerState);
						memcpy(ps + PS_ORIGIN, d.origin, sizeof(d.origin));
						memcpy(ps + PS_VELOCITY, d.velocity, sizeof(d.velocity));
					}
				}
				__except (EXCEPTION_EXECUTE_HANDLER) {}
			}
			return ret;
		}

		// CL_CreateCmd (0x6C6090_b): builds the local usercmd from input (view angles,
		// buttons, weapon). We record it during a match and replay it during playback so
		// the camera looks the right way and the viewmodel/weapon is correct.
		__int64 createcmd_hook(__int64 cl, void* cmd)
		{
			__int64 ret = 0;
			__try { ret = g_createCmdHook.invoke<__int64>(cl, cmd); }
			__except (EXCEPTION_EXECUTE_HANDLER) {}

			if (cmd)
			{
				__try
				{
					const int st = *reinterpret_cast<int*>(cmd); // usercmd_s.serverTime @ 0
					if (!g_playing && g_recording && g_seenUseful && !g_driving)
					{
						cmd_rec rec{}; rec.serverTime = st;
						memcpy(rec.cmd, cmd, USERCMD_SIZE);
						write_record(REC_USERCMD, 0, st, &rec, sizeof(rec), 0, 0, 0, static_cast<unsigned>(st), 0);
					}
					// NOTE: usercmd REPLAY is intentionally disabled — it drives Pmove and
					// fights the directly-injected predicted origin/velocity (movement
					// desync). The archive blob (CL_Demo_UpdateStatsRing) drives the view.
				}
				__except (EXCEPTION_EXECUTE_HANDLER) {}
			}
			return ret;
		}

		// CL_Demo_UpdateStatsRing (0x9CC60_b): builds the 128-byte view/stats blob each
		// rendered frame (from CG_DrawActive). In playback the live build is blank, so we
		// record the real blob during the match and inject it back, keyed by cl_serverTime
		// (0xC5EA44_b). This is what corrects the view angles / on-screen state.
		__int64 updatestats_hook(__int64 a1, int a2)
		{
			__int64 ret = 0;
			__try { ret = g_updateStatsHook.invoke<__int64>(a1, a2); }
			__except (EXCEPTION_EXECUTE_HANDLER) {}

			if (a1)
			{
				__try
				{
					const int st = *reinterpret_cast<int*>(0xC5EA44_b); // cl_serverTime
					if (!g_playing && g_recording && g_seenUseful && !g_driving)
					{
						archive_rec rec{}; rec.serverTime = st;
						memcpy(rec.blob, reinterpret_cast<void*>(a1), ARCHIVE_SIZE);
						write_record(REC_ARCHIVE, a2, st, &rec, sizeof(rec), 0, 0, 0, static_cast<unsigned>(st), 0);
					}
					else if (g_playing)
					{
						const archive_rec& r = g_archiveFrames[st & 255];
						if (r.serverTime != 0) memcpy(reinterpret_cast<void*>(a1), r.blob, ARCHIVE_SIZE);
					}
				}
				__except (EXCEPTION_EXECUTE_HANDLER) {}
			}
			return ret;
		}

		bool isplaying_hook(int client)
		{
			const uintptr_t caller = ptr_to_rva(_ReturnAddress());
			const bool force = (g_playing || g_forceIsPlaying) && is_gamestate_isplaying_site(caller);
			if (force) return true;
			return g_isPlayingHook.invoke<bool>(client);
		}

		void comerror_hook(int code, const char* fmt, uintptr_t a3, uintptr_t a4, uintptr_t a5, uintptr_t a6)
		{
			// Swallow the draw-time backwards-time error ("398") during replay so it
			// doesn't abort playback.
			if ((g_playing || g_armed) && fmt_is_398(fmt)) return;
			g_comErrorHook.invoke<void>(code, fmt, a3, a4, a5, a6);
		}

		// the IsPlaying gamestate call-site check (file RVAs)
		bool is_gamestate_isplaying_site(uintptr_t rva)
		{
			return (rva >= 0x462C18 && rva <= 0x462C24)
				|| (rva >= 0x462D20 && rva <= 0x462D30)
				|| (rva >= 0x462DF4 && rva <= 0x462E04);
		}
	}

	bool is_recording() { return g_recording; }
	bool is_playing() { return g_playing || g_armed; }

	void stop()
	{
		close_playback("user stop");
		GameUtil::Cbuf_AddText(LOCAL_CLIENT_0, "disconnect\n");
	}

	bool play(const std::string& file)
	{
		close_playback("restart");

		const std::string path = "demos/" + file;
		FILE* f = nullptr;
		fopen_s(&f, path.c_str(), "rb");
		if (!f) { Console::printf("[demo] not found: %s", path.c_str()); return false; }

		W2DRHeader h{};
		if (fread(&h, 1, sizeof(h), f) != sizeof(h) || h.magic != W2DR_MAGIC)
		{
			fclose(f); Console::printf("[demo] bad demo file: %s", path.c_str()); return false;
		}

		char map[128]; strncpy_s(map, sizeof(map), h.map[0] ? h.map : "mp_d_day", _TRUNCATE);
		Console::printf("[demo] playing %s (map=%s mode=%s)", file.c_str(), h.map, h.mode);

		// Load the map through the engine's start-connection route, then replay.
		run_map_route(map);

		g_pbFile = f;        // continue reading records after the header
		g_playing = true;
		g_driving = false;

		feed_gamestate();

		// Enter demo-playback mode (CL_Demo_IsPlaying true broadly).
		set_demo_client_mode(0, 2);
		g_armed = true;
		g_naturalSnaps = 0;
		g_pbExceptions = 0;
		g_pbApplied = 0;
		g_pbArmTick = sys_ms();
		g_pbNextTick = sys_ms();
		g_pbHaveFirstTime = false;
		memset(g_clientFrames, 0, sizeof(g_clientFrames));
		memset(g_cmdFrames, 0, sizeof(g_cmdFrames));
		memset(g_archiveFrames, 0, sizeof(g_archiveFrames));

		// Pairs are fed by the CL_Demo_RunFrame hook, paced to their recorded times.
		Console::printf("[demo] armed; paced playback (state=%d)", read_state(0));
		return true;
	}

	void init()
	{
		g_gamestateHook.create(0x461B00_b, &gamestate_hook);
		g_snapshotHook.create(0x4639D0_b, &snapshot_hook);
		g_dispatchHook.create(0x4626E0_b, &dispatch_hook);
		g_isPlayingHook.create(0x90F400_b, &isplaying_hook);
		g_comErrorHook.create(0x8F750_b, &comerror_hook);
		g_initClientHook.create(0x6F830_b, &initclient_hook);
		g_runFrameHook.create(0x85D30_b, &runframe_hook);
		g_execMenuHook.create(0x91D310_b, &execmenu_hook);
		g_savePredictedHook.create(0x464580_b, &save_predicted_hook);
		g_getPredictedHook.create(0x461650_b, &get_predicted_hook);
		g_createCmdHook.create(0x6C6090_b, &createcmd_hook);
		g_updateStatsHook.create(0x9CC60_b, &updatestats_hook);

		GameUtil::addCommand("demo_play", []
		{
			CmdArgs* a = GameUtil::getCmdArgs();
			if (!a || a->argc[a->nesting] < 2) { Console::printf("usage: demo_play <file.w2dr>"); return; }
			demo_custom::play(a->argv[a->nesting][1]);
		});
		GameUtil::addCommand("demo_stop", [] { demo_custom::stop(); });

		Console::printf("[demo] custom demo system ready (auto-record on match; demo_play <file>)");
	}
}
