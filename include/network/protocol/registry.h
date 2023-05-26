#pragma once

#include "network/connection.h"
#include "network/protocol/packet.h"
#include <map>

namespace packet
{

    namespace registry
    {
        using PacketID = unsigned long;

        struct PacketRegistryEntry
        {
            EncodeFn encode;
            DecodeFn decode;

            ConstructorFn constructor;
        };

        class PacketRegistry
        {
        private:
            std::map<PacketID, PacketRegistryEntry> packets;

        public:
            PacketRegistry() { }

            inline PacketID get_packet_id(ConnectionState state, Direction direction, int id)
            {
                return (static_cast<int>(state) << 8) | (static_cast<int>(direction) << 4) | id;
            }

            template<typename T>
            void emplace(ConnectionState state, Direction direction, int id, EncodeFn encode, DecodeFn decode)
            {
                static_assert(std::is_base_of_v<Packet, T>, "T must derive from Packet");

                ConstructorFn constructor = []() -> Packet *
                {
                    return Packet::constructor_wrapper<T>();
                };

                auto pair = std::pair(get_packet_id(state, direction, id), PacketRegistryEntry { .encode = encode, .decode = decode, .constructor = constructor });

                packets.insert(pair);
            }

            PacketRegistryEntry get(ConnectionState state, Direction direction, int id)
            {
                return packets.at(get_packet_id(state, direction, id));
            }
        };
    }
}
