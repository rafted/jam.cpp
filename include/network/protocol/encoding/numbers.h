#pragma once

#include <complex>
#include <stdexcept>
#include <vector>

#include <stdexcept>
#include <vector>

template<typename T>
T read_big_endian(std::vector<char> &data)
{
    static_assert(std::is_integral<T>::value, "T must be an integral type");

    const std::size_t size = sizeof(T);

    if (data.size() < size)
    {
        throw std::length_error("Not enough data to read");
    }

    T value = 0;

    for (std::size_t i = 0; i < size; ++i)
    {
        value = (value << 8) | static_cast<unsigned char>(data[i]);
    }

    data.erase(data.begin(), data.begin() + size);

    return value;
}
