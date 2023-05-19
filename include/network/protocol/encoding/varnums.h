#include <stdexcept>
#include <vector>

const int SEGMENT_BITS = 0x7F;
const int CONTINUE_BIT = 0x80;

template<typename T>
T read_varnum(std::vector<char> &data)
{
    T value = 0;
    int position = 0;

    for (std::size_t i = 0; i < data.size(); ++i)
    {
        char current_byte = data[i];
        value |= static_cast<T>(current_byte & 0x7F) << position;

        if ((current_byte & 0x80) == 0)
        {
            data.erase(data.begin(), data.begin() + i + 1);
            return value;
        }

        position += 7;

        if (position >= sizeof(T) * 8)
        {
            throw std::length_error("VarNum is too big");
        }
    }

    throw std::length_error("VarNum decoding failed");
}

template<typename T>
void write_varnum(std::vector<char> &buffer, T value)
{
    while (true)
    {
        if ((value & ~static_cast<T>(SEGMENT_BITS)) == 0)
        {
            buffer.push_back(static_cast<char>(value));
            return;
        }

        buffer.push_back(static_cast<char>((value & SEGMENT_BITS) | CONTINUE_BIT));

        // Note: Right shift operator >>> is not available in C++. Instead, we use arithmetic right shift.
        value >>= 7;
    }

    return;
}
