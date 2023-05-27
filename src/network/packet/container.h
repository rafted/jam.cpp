#pragma once

#include "network/protocol/encoding/varnums.h"
#include "spdlog/spdlog.h"
#include <algorithm>
#include <cstdint>
#include <vector>

namespace network::packet
{
    struct PacketContainer
    {
        int32_t length;
        int32_t id;
        std::vector<char> data;

        static PacketContainer read_packet(std::vector<char> &data);
    };
}
