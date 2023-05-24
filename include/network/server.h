#pragma once

#include "network/connection.h"
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
    std::shared_ptr<uvw::loop> loop;
    std::shared_ptr<uvw::tcp_handle> tcp_handle;

    Properties properties;

    Server(std::shared_ptr<uvw::loop> loop, Properties properties)
        : loop(loop)
        , properties(properties)
    {
    }

    void start();
};
