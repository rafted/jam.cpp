#include "network/packet/container.hpp"
#include "network/protocol/encoding/varnums.hpp"

using namespace network::protocol::encoding;

namespace network::packet
{
    PacketContainer PacketContainer::read_packet(std::vector<char> &data)
    {
        int32_t pkt_len = read_varnum<int32_t>(data) + 1;
        int32_t pkt_id = read_varnum<int32_t>(data);
        std::vector<char> pkt_data(data.begin(), data.begin() + pkt_len);

        // construct PacketContainer
        PacketContainer container = {
            .length = pkt_len,
            .id = pkt_id,
            .data = pkt_data
        };

        return container;
    }
}
