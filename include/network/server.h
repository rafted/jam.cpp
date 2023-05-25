#pragma once

#include "network/connection.h"
#include "network/protocol/packet.h"
#include "network/protocol/proto_47.h"
#include <memory>
#include <spdlog/spdlog.h>
#include <string>
#include <uvw.hpp>
#include <uvw/loop.h>
#include <uvw/tcp.h>

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

    std::unique_ptr<PacketRegistry> packet_registry;

    Server(std::shared_ptr<uvw::loop> loop, Properties properties)
        : loop(loop)
        , properties(properties)
    {
        packet_registry = std::make_unique<PacketRegistry>(proto_47::make_packet_registry());
    }

    void start();
};
