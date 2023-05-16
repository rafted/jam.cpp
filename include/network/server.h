#pragma once

#include "network/connection.h"
#include <memory>
#include <spdlog/spdlog.h>
#include <string>
#include <uvw.hpp>
#include <uvw/loop.h>
#include <uvw/tcp.h>

class Server
{
public:
    std::string host;
    int port;

    std::shared_ptr<uvw::loop> loop;
    std::shared_ptr<uvw::tcp_handle> tcp_handle;

    Server(std::shared_ptr<uvw::loop> loop, std::string host, int port)
        : loop(loop)
        , host(host)
        , port(port)
    {
    }

    void start();
};
