#pragma once
#include "structs.h"
#include "DemoData.hpp"

#include <optional>
#include <string>
#include <list>
#include <fstream>
#include <memory>

// Ported from Airyzz/s1-mod via s2-mod (demo_playback.h), adapted to S2MP-Mod.
//
// NOTE: s2-mod drives playback through the demonware theater_server + "connect demo".
// S2MP-Mod has no demonware layer, so this port uses an EXPERIMENTAL direct-injection
// pump (see DemoPlayback.cpp) instead of the network path. The on-disk .demo format
// and the reader are unchanged.
namespace demo_playback
{
	class demo_reader
	{
	private:
		int time;
		int firstMessageTime;
		int offsetTime;
		std::streamoff firstMessageFileOffset;
		int sequenceNumber;
		std::ifstream stream;
		std::string map;
		std::string mode;
		std::list<std::string> server_queue;
		demo_data::demo_client_data_t last_client_data;
		demo_data::demo_client_data_t frames[256];

		bool peek_next_message_time(int& out);

		void read_server_message();
		void read_client_data();
		void read_message();

	public:
		demo_reader(std::string filepath);

		bool is_open();
		std::optional<demo_data::demo_client_data_t> get_client_data_for_time(int time);
		std::optional<std::string> dequeue_server_message();
		std::string get_map_name();
		std::string get_mode();

		void read_frame(int ms);
		void close();
		void restart();
		void jump_to(int time);
		int get_time();
	};

	bool is_paused();
	bool is_playing();
	std::shared_ptr<demo_reader> get_current_demo_reader();

	void init();
}
