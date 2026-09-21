#include "pch.h"
#include "demo/demo_library.hpp"

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <fstream>
#include <vector>

namespace demo_library
{
	namespace
	{
		constexpr std::uint32_t DEMO_VERSION = 29;      // header +0x00 and footer magic
		constexpr std::uint32_t HEADER_SIZE = 79384;    // header +0x04, ALSO the body offset
		constexpr std::uint32_t FOOTER_TAG = 3984;      // footer body [1]
		constexpr std::size_t   MAP_NAME_OFF = 272;     // footer body + 272
		constexpr std::size_t   ARCHIVE_SIZE = 185;     // 1 type + 184 payload
		constexpr std::size_t   ARCHIVE_TIME_OFF = 37;  // serverTime inside the packet
		constexpr std::size_t   ARCHIVE_GATE_OFF = 53;  // non-zero adds 6 bytes

		bool read_at(std::ifstream& f, std::streamoff off, void* dst, std::size_t n)
		{
			f.clear();
			f.seekg(off, std::ios::beg);
			if (!f)
			{
				return false;
			}
			f.read(static_cast<char*>(dst), static_cast<std::streamsize>(n));
			return static_cast<std::size_t>(f.gcount()) == n;
		}

		std::string file_date(const std::filesystem::path& p)
		{
			// last_write_time is a file_clock; going through the system clock is
			// the portable route to a calendar date.
			std::error_code ec;
			const auto ft = std::filesystem::last_write_time(p, ec);
			if (ec)
			{
				return {};
			}
			const auto sys = std::chrono::clock_cast<std::chrono::system_clock>(ft);
			const std::time_t t = std::chrono::system_clock::to_time_t(sys);
			std::tm tm{};
			if (localtime_s(&tm, &t) != 0)
			{
				return {};
			}
			char buf[32]{};
			std::snprintf(buf, sizeof(buf), "%04d-%02d-%02d %02d:%02d",
				tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min);
			return buf;
		}

		// Header + footer, i.e. everything that is two seeks away.
		Info read_head(const std::filesystem::path& path, std::ifstream& f)
		{
			Info info;
			std::error_code ec;
			info.size = std::filesystem::file_size(path, ec);
			if (ec)
			{
				info.size = 0;
			}
			info.date = file_date(path);

			std::uint32_t hdr[3]{};
			if (!read_at(f, 0, hdr, sizeof(hdr)))
			{
				info.reason = "too small to be a demo";
				return info;
			}
			if (hdr[0] != DEMO_VERSION)
			{
				info.reason = "wrong demo version";
				return info;
			}
			if (hdr[1] != HEADER_SIZE)
			{
				// A demo from a different build. CL_Demo_Play_f rejects these
				// outright, so say so rather than listing it as playable.
				info.reason = "recorded by a different build";
				return info;
			}
			info.client = hdr[2];

			// Footer: the last 8 bytes are [size][magic], and the body starts
			// footerSize before them -- exactly what CL_Demo_ReadFooter does.
			if (info.size < 16)
			{
				info.reason = "truncated";
				return info;
			}
			std::uint32_t tail[2]{};
			if (!read_at(f, static_cast<std::streamoff>(info.size) - 8, tail, sizeof(tail)))
			{
				info.reason = "no footer";
				return info;
			}
			const std::uint32_t footer_size = tail[0];
			if (tail[1] != DEMO_VERSION || footer_size == 0
				|| static_cast<std::uintmax_t>(footer_size) + 8 >= info.size)
			{
				// Almost always a recording the game was killed during, so the
				// footer was never written. That demo will not play.
				info.reason = "footer missing or damaged (recording interrupted?)";
				return info;
			}

			const auto body = static_cast<std::streamoff>(info.size) - 8
				- static_cast<std::streamoff>(footer_size);
			std::uint32_t tags[2]{};
			if (!read_at(f, body, tags, sizeof(tags))
				|| tags[0] != DEMO_VERSION || tags[1] != FOOTER_TAG)
			{
				info.reason = "footer tags wrong";
				return info;
			}

			char name[64]{};
			if (read_at(f, body + static_cast<std::streamoff>(MAP_NAME_OFF), name, sizeof(name) - 1))
			{
				name[sizeof(name) - 1] = 0;
				// Must look like a map name, or we are reading the wrong place.
				bool sane = name[0] != 0;
				for (const char* c = name; *c; ++c)
				{
					if (!(std::isalnum(static_cast<unsigned char>(*c)) || *c == '_' || *c == '-'))
					{
						sane = false;
						break;
					}
				}
				if (sane)
				{
					info.map = name;
				}
			}

			info.ok = true;
			return info;
		}

		// Walk the byte-tagged packet stream for the first and last archive
		// serverTime. Reads sequentially and never decompresses anything.
		std::int32_t walk_duration(std::ifstream& f, std::uintmax_t file_size)
		{
			std::streamoff pos = HEADER_SIZE;
			std::int32_t first = 0, last = 0;
			bool have_first = false;

			std::vector<char> pkt(ARCHIVE_SIZE);
			// Bounded so a malformed file cannot spin: a 3 MB demo is ~25k packets.
			for (int guard = 0; guard < 400000; ++guard)
			{
				unsigned char type = 0;
				if (!read_at(f, pos, &type, 1))
				{
					break;
				}
				if (type == 0)
				{
					break;                       // clean end of stream
				}
				if (type == 1)
				{
					if (!read_at(f, pos, pkt.data(), ARCHIVE_SIZE))
					{
						break;
					}
					std::int32_t t = 0;
					std::memcpy(&t, pkt.data() + ARCHIVE_TIME_OFF, 4);
					std::uint32_t gate = 0;
					std::memcpy(&gate, pkt.data() + ARCHIVE_GATE_OFF, 4);
					if (!have_first)
					{
						first = t;
						have_first = true;
					}
					last = t;
					// The conditional +6 has never fired in a shipped demo, but
					// honour it: getting a packet size wrong desyncs the walk.
					pos += static_cast<std::streamoff>(ARCHIVE_SIZE) + (gate ? 6 : 0);
					continue;
				}
				if (type == 2 || type == 3)
				{
					// 2: [1][seq 4][len 4][len]      3: [1][seq 4][extra 4][len 4][len]
					const std::streamoff len_at = pos + 1 + 4 + (type == 3 ? 4 : 0);
					std::uint32_t len = 0;
					if (!read_at(f, len_at, &len, 4) || len > 0x20000)
					{
						break;
					}
					pos = len_at + 4 + static_cast<std::streamoff>(len);
					continue;
				}
				break;                           // type 4 (commands) or garbage
			}

			if (!have_first || last <= first)
			{
				return -1;
			}
			// Guard against a wild value from a mis-stepped walk rather than
			// reporting a 400-hour demo.
			const std::int64_t d = static_cast<std::int64_t>(last) - first;
			return (d > 0 && d < 24LL * 60 * 60 * 1000) ? static_cast<std::int32_t>(d) : -1;
		}
	}

	Info describe_custom(const std::filesystem::path& path)
	{
		Info info;
		std::error_code ec;
		info.size = std::filesystem::file_size(path, ec);
		if (ec)
		{
			info.size = 0;
		}
		info.date = file_date(path);

		std::ifstream f(path, std::ios::binary);
		if (!f)
		{
			info.reason = "cannot open";
			return info;
		}
		// The header chunks all sit at the very start, so one small read covers
		// them. Chunk framing is demo_utils' write_id_and_size: an id byte whose
		// 0x80 bit means "one-byte size", otherwise a u32 size; id = byte & ~0xE0;
		// 31 = eof. map_header (id 1) payload = "<map>\0<gametype>\0".
		char buf[4096]{};
		f.read(buf, sizeof(buf));
		const std::size_t n = static_cast<std::size_t>(f.gcount());

		std::size_t off = 0;
		for (int chunk = 0; chunk < 16 && off < n; ++chunk)
		{
			const auto id_byte = static_cast<std::uint8_t>(buf[off++]);
			const int id = id_byte & ~0xE0 & 0xFF;
			if (id == 31)
			{
				break;
			}
			std::uint32_t size = 0;
			if (id_byte & 0x80)
			{
				if (off + 1 > n) break;
				size = static_cast<std::uint8_t>(buf[off++]);
			}
			else
			{
				if (off + 4 > n) break;
				std::memcpy(&size, buf + off, 4);
				off += 4;
			}
			if (id == 1)
			{
				const std::size_t end = (std::min)(n, off + static_cast<std::size_t>(size));
				std::string map;
				for (std::size_t i = off; i < end && buf[i] != '\0'; ++i)
				{
					map += buf[i];
				}
				if (!map.empty())
				{
					info.map = std::move(map);
					info.ok = true;
				}
				break;
			}
			off += size;
		}
		if (!info.ok)
		{
			info.reason = "no map header in the first 4 KB";
		}
		return info;
	}

	Info describe(const std::filesystem::path& path)
	{
		std::ifstream f(path, std::ios::binary);
		if (!f)
		{
			Info bad;
			bad.reason = "cannot open";
			return bad;
		}
		return read_head(path, f);
	}

	Info describe_full(const std::filesystem::path& path)
	{
		std::ifstream f(path, std::ios::binary);
		if (!f)
		{
			Info bad;
			bad.reason = "cannot open";
			return bad;
		}
		Info info = read_head(path, f);
		if (info.ok)
		{
			info.duration_ms = walk_duration(f, info.size);
		}
		return info;
	}

	std::string suggest_name(const std::filesystem::path& path, const Info& info)
	{
		std::string map = info.map;
		if (map.empty())
		{
			map = path.stem().string();
		}

		std::string date = info.date;               // "YYYY-MM-DD HH:MM"
		std::string stamp;
		for (char c : date)
		{
			if (std::isdigit(static_cast<unsigned char>(c)))
			{
				stamp += c;
			}
			else if (c == '-')
			{
				stamp += '-';
			}
			else if (c == ' ')
			{
				stamp += '_';
			}
			// ':' dropped -- illegal in a filename
		}
		if (stamp.empty())
		{
			return map;
		}
		return map + "_" + stamp;
	}

	std::optional<std::filesystem::path> rename(const std::filesystem::path& path,
		const std::string& new_stem, std::string& why)
	{
		why.clear();
		if (new_stem.empty())
		{
			why = "empty name";
			return std::nullopt;
		}
		// A demo name reaches the engine as `cl_demo_play <stem>`, so anything
		// the command parser or the filesystem would choke on is refused here
		// rather than producing a file that cannot be played.
		for (char c : new_stem)
		{
			if (std::strchr("\\/:*?\"<>| \t", c) != nullptr)
			{
				why = "name contains a character that is not allowed";
				return std::nullopt;
			}
		}

		std::error_code ec;
		auto dst = path.parent_path() / (new_stem + path.extension().string());
		if (dst == path)
		{
			return dst;                              // already correct
		}
		if (std::filesystem::exists(dst, ec))
		{
			// Never clobber a recording. Suffix instead.
			for (int i = 2; i < 100; ++i)
			{
				auto alt = path.parent_path()
					/ (new_stem + "_" + std::to_string(i) + path.extension().string());
				if (!std::filesystem::exists(alt, ec))
				{
					dst = alt;
					break;
				}
			}
			if (std::filesystem::exists(dst, ec))
			{
				why = "a demo with that name already exists";
				return std::nullopt;
			}
		}

		std::filesystem::rename(path, dst, ec);
		if (ec)
		{
			why = ec.message();
			return std::nullopt;
		}
		return dst;
	}

	std::optional<std::filesystem::path> auto_rename(const std::filesystem::path& path,
		std::string& why)
	{
		const Info info = describe(path);
		if (!info.ok || info.map.empty())
		{
			why = info.reason.empty() ? "map name unreadable" : info.reason;
			return std::nullopt;
		}
		// Already named by us? The engine's own names are x<4hex>_<8hex>, so a
		// stem starting with the map name means we have been here before.
		const auto stem = path.stem().string();
		if (stem.rfind(info.map, 0) == 0)
		{
			return path;
		}
		return rename(path, suggest_name(path, info), why);
	}

	bool remove(const std::filesystem::path& path, std::string& why)
	{
		why.clear();
		std::error_code ec;
		if (!std::filesystem::remove(path, ec) || ec)
		{
			why = ec ? ec.message() : std::string("file not found");
			return false;
		}
		return true;
	}

	std::string human_size(std::uintmax_t bytes)
	{
		char buf[32]{};
		if (bytes >= 1024ull * 1024)
		{
			std::snprintf(buf, sizeof(buf), "%.1f MB",
				static_cast<double>(bytes) / (1024.0 * 1024.0));
		}
		else
		{
			std::snprintf(buf, sizeof(buf), "%.0f KB", static_cast<double>(bytes) / 1024.0);
		}
		return buf;
	}

	std::string human_duration(std::int32_t ms)
	{
		if (ms < 0)
		{
			return "?";
		}
		const int total = ms / 1000;
		char buf[32]{};
		if (total >= 3600)
		{
			std::snprintf(buf, sizeof(buf), "%d:%02d:%02d",
				total / 3600, (total / 60) % 60, total % 60);
		}
		else
		{
			std::snprintf(buf, sizeof(buf), "%d:%02d", total / 60, total % 60);
		}
		return buf;
	}
}
