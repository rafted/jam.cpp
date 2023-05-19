#include <stdexcept>
#include <vector>

const int SEGMENT_BITS = 0x7F;
const int CONTINUE_BIT = 0x80;

template<typename T>
T read_varnum(const std::vector<unsigned char> &data)
{
    T value = 0;
    int position = 0;
    unsigned char current_byte;

    for (const auto &byte : data)
    {
        current_byte = byte;
        value |= (T) (current_byte & 0x7F) << position;

        if ((current_byte & 0x80) == 0)
            break;

        position += 7;

        if (position >= sizeof(T) * 8)
            throw std::length_error("VarNum is too big");
    }

    return value;
}

template<typename T>
std::vector<unsigned char> write_varnum(std::vector<unsigned char> &output, T value)
{
    while (true)
    {
        if ((value & ~static_cast<T>(SEGMENT_BITS)) == 0)
        {
            output.push_back(static_cast<unsigned char>(value));
            return output;
        }

        output.push_back(static_cast<unsigned char>((value & SEGMENT_BITS) | CONTINUE_BIT));

        // Note: Right shift operator >>> is not available in C++. Instead, we use arithmetic right shift.
        value >>= 7;
    }
}
