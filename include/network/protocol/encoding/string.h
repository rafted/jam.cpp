#pragma once

#include "network/protocol/encoding/varnums.h"
#include <array>
#include <cstdint>
#include <cstring>
#include <stdexcept>
#include <string>
#include <vector>

inline std::string read_string(std::vector<char> &data)
{
    std::int32_t length = read_varnum<std::int32_t>(data);

    if (static_cast<std::size_t>(length) > data.size())
    {
        throw std::length_error("not enough data to fill buffer");
    }

    std::string result(data.begin(), data.begin() + length);

    data.erase(data.begin(), data.begin() + length);
    data.shrink_to_fit();

    return result;
}

inline void write_string(std::vector<char> &buffer, const std::string &str)
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
