#pragma once

#include <memory>
#include <string>
#include <uvw.hpp>
#include <uvw/loop.h>
#include <uvw/tcp.h>

class Server
{
public:
    std::shared_ptr<uvw::loop> loop;
    std::shared_ptr<uvw::tcp_handle> tcp_handle;

    Server(std::shared_ptr<uvw::loop> loop)
        : loop(loop)
    {
    }

    void start(std::string host, int port);
};
