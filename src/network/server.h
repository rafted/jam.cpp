#pragma once

#include "network/protocol/implementations/proto_47.h"
#include <memory>
#include <network/packet/registry.h>
#include <string>
#include <uvw.hpp>
#include <uvw/loop.h>
#include <uvw/tcp.h>

using namespace network::packet::registry;

namespace network
{
    struct Properties
    {
        std::string host;
        int port;

        int protocol;
    };

    class Server
    {
    public:
        Properties properties;

        std::shared_ptr<uvw::loop> loop;
        std::shared_ptr<uvw::tcp_handle> tcp_handle;

        PacketRegistry packet_registry;

        Server(std::shared_ptr<uvw::loop> loop, const Properties properties)
            : loop(loop)
            , properties(properties)
        {
            packet_registry = proto_47::make_packet_registry();
        }

        void start();
    };
}
