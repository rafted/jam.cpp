#pragma once

#include "network/packet/container.h"
#include "network/packet/packet.h"
#include "network/packet/registry.h"
#include "network/protocol/encoding/numbers.h"
#include "network/protocol/encoding/string.h"
#include <string>

using namespace network::protocol::encoding;
using namespace network::packet;
using namespace network::packet::registry;

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

        registry.emplace<handshaking::serverbound::HandshakePacket>(
            network::Handshake,
            network::packet::Direction::Serverbound,
            0,
            network::packet::registry::PacketRegistry::make_constructor<handshaking::serverbound::HandshakePacket>());

        return registry;
    }

}
