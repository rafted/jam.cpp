#include "network/packet/registry.h"

namespace network::packet::registry
{
    PacketRegistryEntry PacketRegistry::get(ConnectionState state, Direction direction, int id)
    {
        return packets.at(get_packet_id(state, direction, id));
    }
}
