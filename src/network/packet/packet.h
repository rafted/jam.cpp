#pragma once

#include "network/packet/container.h"
#include <functional>
#include <map>
#include <memory>
#include <spdlog/spdlog.h>
#include <tuple>
#include <type_traits>

using namespace network::packet;

namespace network::packet
{
    enum Direction
    {
        Serverbound,
        Clientbound
    };

    class Packet
    {
        virtual PacketContainer encode() = 0;
        virtual void decode(PacketContainer container) = 0;

    public:
        static PacketContainer encode_wrapper(void *packet)
        {
            Packet *p = static_cast<Packet *>(packet);
            return p->encode();
        }

        static PacketContainer decode_wrapper(void *packet, PacketContainer container)
        {
            Packet *p = static_cast<Packet *>(packet);
            p->decode(container);
            return container;
        }

        template<typename T>
        static Packet *constructor_wrapper()
        {
            static_assert(std::is_base_of_v<Packet, T>, "T must derive from Packet");

            T *newPacket = new T();

            return static_cast<Packet *>(newPacket);
        }
    };
}
