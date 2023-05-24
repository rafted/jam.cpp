#pragma once

#include "network/container.h"
#include "network/protocol/encoding/numbers.h"
#include "network/protocol/encoding/string.h"
#include "network/protocol/encoding/varnums.h"
#include "network/protocol/packet.h"
#include <string>

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
                int32_t protocol_version;
                std::string server_address;
                unsigned short server_port;
                int32_t next_state;

                HandshakePacket() { }

                PacketContainer encode() override
                {
                    return PacketContainer {};
                }

                void decode(PacketContainer container) override
                {
                    this->protocol_version = read_varnum<int32_t>(container.data);
                    this->server_address = read_string(container.data);
                    this->server_port = read_big_endian<unsigned short>(container.data);
                    this->next_state = read_varnum<int32_t>(container.data);
                }
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

    static PacketRegistry make_packet_registry()
    {
        PacketRegistry registry;

        // registry.emplace<handshaking::serverbound::HandshakePacket>(
        //     Serverbound,
        //     0,
        //     &handshaking::serverbound::HandshakePacket::encode,
        //     &handshaking::serverbound::HandshakePacket::decode);

        registry.emplace<handshaking::serverbound::HandshakePacket>(
            Serverbound,
            0,
            &Packet::EncodeWrapper,
            &Packet::DecodeWrapper);

        return registry;
    }

}
