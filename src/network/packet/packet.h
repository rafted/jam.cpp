#pragma once

#include "network/packet/container.h"

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
    public:
        virtual PacketContainer encode() = 0;
        virtual void decode(PacketContainer container) = 0;
    };
}
