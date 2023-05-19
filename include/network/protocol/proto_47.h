#pragma once

#include "network/protocol/packet.h"

namespace proto_47
{

    namespace handshaking
    {

        namespace clientbound
        {
        }

        namespace serverbound
        {
            class HandshakePacket : public Packet
            {
            public:
                void decode(PacketContainer container) override {

                };
            };
        }

    }

    namespace play
    {

        namespace clientbound
        {
        }

        namespace serverbound
        {
        }

    }

    namespace status
    {

        namespace clientbound
        {
        }

        namespace serverbound
        {
        }

    }

    namespace login
    {

        namespace clientbound
        {
        }

        namespace serverbound
        {
        }

    }

}
