#pragma once

#include "network/protocol/encoding/varnums.h"
#include "spdlog/spdlog.h"
#include <algorithm>
#include <cstdint>
#include <vector>

struct PacketContainer
{
    int32_t length;
    int32_t id;
    std::vector<char> data;

    static PacketContainer read_packet(std::vector<char> &data)
    {
        int32_t pkt_len = read_varnum<int32_t>(data) + 1;
        int32_t pkt_id = read_varnum<int32_t>(data);
        std::vector<char> pkt_data(data.begin(), data.begin() + pkt_len);

        // construct PacketContainer
        PacketContainer container = {};
        container.length = pkt_len;
        container.id = pkt_id;
        container.data = pkt_data;

        return container;
    }
};
