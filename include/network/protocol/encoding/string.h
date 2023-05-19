#include "network/protocol/encoding/varnums.h"
#include <cstdint>
#include <cstring>
#include <stdexcept>
#include <string>
#include <array>
#include <vector>

void write_string(std::vector<char> &buffer, const std::string &str)
{
    const std::size_t length = str.length();
    if (length > 32767)
    {
        throw std::length_error("String length exceeds the maximum limit");
    }

    // write the length of the string
    write_varnum<int32_t>(buffer, static_cast<std::int32_t>(length));

    // reserve memory to avoid reallocation
    const std::size_t old_size = buffer.size();
    buffer.resize(old_size + length);

    std::memcpy(&buffer[old_size], str.data(), length);
}
