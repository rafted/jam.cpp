#pragma once

#include "network/connection.h"
#include "network/packet/packet.h"
#include <map>

namespace network::packet::registry
{
    using PacketID = unsigned long;
    using Constructor = std::function<Packet *()>;

    class PacketRegistry
    {
    private:
        std::unordered_map<PacketID, Constructor> packets;

    public:
        PacketRegistry() { }

        inline PacketID get_packet_id(ConnectionState state, Direction direction, int id)
        {
            return (static_cast<int>(state) << 8) | (static_cast<int>(direction) << 4) | id;
        }

        template<typename T>
        void emplace(ConnectionState state, Direction direction, int id, Constructor constructor)
        {
            static_assert(std::is_base_of_v<Packet, T>, "T must derive from Packet");

            packets.insert(std::pair(get_packet_id(state, direction, id), constructor));
        }

        std::optional<Constructor> get(ConnectionState state, Direction direction, int id);

        template<typename T>
        static Constructor make_constructor()
        {
            return []()
            { return new T(); };
        }
    };
}
