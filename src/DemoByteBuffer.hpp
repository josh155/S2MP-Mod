#pragma once
#include <string>
#include <cstring>
#include <cstdint>

// Slim, self-contained port of s2-mod's demonware::byte_buffer, trimmed to the
// subset the demo system uses. The demo path always runs with data-types
// disabled, so the on-disk format is raw little-endian:
//   int32 -> 4 raw bytes
//   blob  -> [int32 length][raw bytes]
// This is byte-for-byte compatible with the s1/s2-mod .demo format, which the
// playback reader parses with raw stream reads.
namespace demo
{
	class byte_buffer final
	{
	public:
		byte_buffer() = default;

		explicit byte_buffer(std::string buffer) : buffer_(std::move(buffer)) {}

		void set_use_data_types(const bool use_data_types)
		{
			this->use_data_types_ = use_data_types;
		}

		bool is_using_data_types() const { return this->use_data_types_; }

		bool write(const int bytes, const void* data)
		{
			this->buffer_.append(static_cast<const char*>(data), bytes);
			return true;
		}

		bool write(const std::string& data)
		{
			return this->write(static_cast<int>(data.size()), data.data());
		}

		bool write_data_type(unsigned char data)
		{
			if (!this->use_data_types_) return true;
			return this->write(sizeof(data), &data);
		}

		bool write_int32(int data)
		{
			this->write_data_type(BD_BB_SIGNED_INTEGER32_TYPE);
			return this->write(sizeof(data), &data);
		}

		bool write_uint32(unsigned int data)
		{
			this->write_data_type(BD_BB_UNSIGNED_INTEGER32_TYPE);
			return this->write(sizeof(data), &data);
		}

		bool write_string(const char* data)
		{
			this->write_data_type(BD_BB_SIGNED_CHAR8_STRING_TYPE);
			return this->write(static_cast<int>(std::strlen(data)) + 1, data);
		}

		bool write_string(const std::string& data)
		{
			return this->write_string(data.data());
		}

		bool write_blob(const char* data, const int length)
		{
			this->write_data_type(BD_BB_BLOB_TYPE);
			this->write_uint32(static_cast<unsigned int>(length));
			return this->write(length, data);
		}

		bool write_blob(const std::string& data)
		{
			return this->write_blob(data.data(), static_cast<int>(data.size()));
		}

		// ---- reads (used by the theater server to parse handshake packets) ----
		bool read(int bytes, void* output)
		{
			if (static_cast<size_t>(bytes) + this->current_byte_ > this->buffer_.size())
			{
				return false;
			}
			std::memmove(output, this->buffer_.data() + this->current_byte_, bytes);
			this->current_byte_ += bytes;
			return true;
		}

		bool read_int32(int* output)
		{
			return this->read(sizeof(*output), output);
		}

		bool read_string(std::string* output)
		{
			const char* start = this->buffer_.data() + this->current_byte_;
			const size_t remaining = this->buffer_.size() - this->current_byte_;
			const size_t len = strnlen(start, remaining);
			output->assign(start, len);
			this->current_byte_ += len + 1; // skip the null terminator too
			return true;
		}

		std::string& get_buffer() { return this->buffer_; }
		size_t size() const { return this->buffer_.size(); }

	private:
		// demonware data-type tags (only emitted when use_data_types_ is true)
		static constexpr unsigned char BD_BB_SIGNED_INTEGER32_TYPE = 4;
		static constexpr unsigned char BD_BB_UNSIGNED_INTEGER32_TYPE = 5;
		static constexpr unsigned char BD_BB_SIGNED_CHAR8_STRING_TYPE = 9;
		static constexpr unsigned char BD_BB_BLOB_TYPE = 10;

		std::string buffer_;
		size_t current_byte_ = 0;
		bool use_data_types_ = true;
	};
}
