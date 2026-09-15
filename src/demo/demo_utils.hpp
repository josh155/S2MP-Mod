#pragma once

#include "demo_game.hpp"

#include <array>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <optional>
#include <span>
#include <string>
#include <string_view>
#include <vector>

namespace demo_utils
{
	bool is_demo_feeding();

	inline constexpr std::string_view DEMO_CODE_VERSION = "s2-v0.1.0";
	inline constexpr std::string_view DEMO_EXTENSION = ".dm_s2";
	// Large enough for zlib-compressed configstring blob (H1 update_gamestate_data).
	inline constexpr std::size_t MAX_SIZE = 524'288;

	enum class demo_data_id : std::uint8_t
	{
		mod_header = 0,
		map_header = 1,
		network_data = 2,
		predicted_data = 3,
		update_gamestate_data = 4,
		gen_header = 5,
	gen_footer = 6,
		gamestate_message = 7,
		eof = 31,
		flags = 0b1110'0000,
		one_byte_flag = 0b1000'0000,
	};

	enum class predicted_data_id : std::uint8_t
	{
		player = 0,
	};

#pragma pack(push, 1)
	struct packed_gamestate_sizes
	{
		std::uint64_t string_data : 20;
		std::uint64_t string_offsets : 16;
		std::uint64_t unused : 27;
		std::uint64_t compressed : 1;
	};
#pragma pack(pop)
	static_assert(sizeof(packed_gamestate_sizes) == 8, "packed_gamestate_sizes");

	// H1 killsreak HUD stub — written for format parity; zeros on S2 for now.
	struct persistent_data_t
	{
		std::int32_t cur_kill_count{};
		std::int32_t req_kill_count_next_ksr{};
		std::int32_t unknown1{1};
		std::int32_t active_ksr_count{};
		std::int32_t unknown2{-1};
		std::int32_t active_ksr_flags{};
		std::int32_t unknown3{};
		std::int32_t first_ksr_icon{};
		std::int32_t second_ksr_icon{};
		std::int32_t third_ksr_icon{};
	};
	static_assert(sizeof(persistent_data_t) == 40, "persistent_data_t");

	struct gamestate_t
	{
		std::uint32_t svr_cmd_seq{};
		std::int32_t data_count{};
		std::vector<std::uint8_t> string_offsets; // MAX_CONFIGSTRINGS * 4
		std::vector<std::uint8_t> string_data;    // data_count bytes (up to 0x20000)
	};

	struct predicted_sample_t
	{
		demo_game::ClientArchiveEntry cad{};
		demo_game::vec3_t viewangles{};
	};

	struct loaded_demo
	{
		std::string map;
		std::string gametype;
		std::vector<std::uint8_t> network;
		std::array<predicted_sample_t, 256> predicted{};
		std::size_t predicted_index{};
		std::optional<std::pair<std::int32_t, std::int32_t>> time_bounds;
		std::size_t post_map_header_offset{};
		std::optional<gamestate_t> gamestate;
	};

	demo_data_id operator|(demo_data_id lhs, demo_data_id rhs);
	demo_data_id operator&(demo_data_id lhs, demo_data_id rhs);

	std::string_view get_dvar_string(std::string_view name, bool allow_empty);
	std::string get_mapname_lower(bool fallback);
	std::string get_gametype_lower(bool fallback);
	std::string get_short_mapname_lower(bool fallback);
	std::optional<std::filesystem::path> demos_directory();
	std::optional<std::filesystem::path> next_demo_path(const std::filesystem::path& dir);

	void write_id_and_size(std::ostream& out, demo_data_id id, std::size_t size);
	void write_id_and_size(std::vector<std::uint8_t>& out, demo_data_id id, std::size_t size);
	void write_network_data(std::ostream& out, std::span<const std::uint8_t> data);
	void write_network_data(std::vector<std::uint8_t>& out, std::span<const std::uint8_t> data);
	void write_gamestate_message(std::ostream& out, std::span<const std::uint8_t> data);
	void write_gamestate_message(std::vector<std::uint8_t>& out, std::span<const std::uint8_t> data);
	void write_predicted_player(std::ostream& out, const predicted_sample_t& sample, std::uint8_t index);
	void write_predicted_player(std::vector<std::uint8_t>& out, const predicted_sample_t& sample, std::uint8_t index);
	void write_mod_header(std::ostream& out);
	void write_mod_header(std::vector<std::uint8_t>& out);
	bool write_map_header(std::ostream& out);
	bool write_map_header(std::vector<std::uint8_t>& out);
	void write_general_header(std::ostream& out);
	void write_general_header(std::vector<std::uint8_t>& out);
	void write_general_footer(std::ostream& out, std::int32_t first, std::int32_t last);
	void write_end_of_file(std::ostream& out);

	// H1 update_gamestate_data — snapshot live configstrings + serverCommandSequence.
	bool write_gamestate_data(std::ostream& out);
	bool write_gamestate_data(std::vector<std::uint8_t>& out);

	bool load_demo_file(const std::filesystem::path& path, loaded_demo& out);
	void process_network_data(std::span<const std::uint8_t> buffer);
	void process_predicted_data(std::span<const std::uint8_t> buffer, loaded_demo& demo);
	void process_gamestate_data(std::span<const std::uint8_t> buffer, std::optional<gamestate_t>& out);
	bool apply_recorded_gamestate(const gamestate_t& gs);
	void note_command_baseline(int svr_cmd_seq);

	bool continue_demo_reading();
	// How far AHEAD of the render clock the feed keeps the newest snapshot, in ms.
	// One 20 Hz snapshot interval (50) by default; 0 restores the pre-fix gate, which
	// left the render clock past the newest snapshot on ~38% of frames.
	int interp_lead_ms();
	void set_interp_lead_ms(int ms);
	void reset_demo_read_gate();
	void fast_forward_demo(std::uint32_t msec);

	namespace zlib
	{
		std::vector<std::uint8_t> compress(std::span<const std::uint8_t> input);
		std::vector<std::uint8_t> decompress(std::span<const std::uint8_t> input, std::size_t hint);
	}
}
