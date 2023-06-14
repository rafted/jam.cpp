#include "network/packet/registry.h"
#include <optional>

namespace network::packet::registry
{
    std::optional<Constructor> PacketRegistry::get(ConnectionState state, Direction direction, int id)
    {
        int pkt_id = get_packet_id(state, direction, id);

        auto it = packets.find(pkt_id);
        if (it == packets.end())
        {
            return std::nullopt;
        }

        return it->second;
    }
}
