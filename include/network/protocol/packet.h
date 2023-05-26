#pragma once

#include "network/container.h"
#include <functional>
#include <map>
#include <memory>
#include <spdlog/spdlog.h>
#include <tuple>
#include <type_traits>

namespace packet
{
    enum Direction
    {
        Serverbound,
        Clientbound
    };

    class Packet
    {
        virtual PacketContainer encode() { }
        virtual void decode(PacketContainer container) { }

    public:
        static PacketContainer encode_wrapper(Packet &packet)
        {
            return packet.encode();
        }

        static PacketContainer decode_wrapper(Packet &packet, PacketContainer container)
        {
            packet.decode(container);
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

    using EncodeFn = PacketContainer (*)(Packet &);
    using DecodeFn = PacketContainer (*)(Packet &, PacketContainer);
    using ConstructorFn = Packet *(*) ();
}
