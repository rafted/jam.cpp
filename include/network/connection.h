#pragma once

#include <memory>
#include <uvw.hpp>
#include <uvw/tcp.h>

enum ConnectionState
{
    Handshake,
    Status,
    Login,
    Play,
    Closed
};

class Connection
{
public:
    std::shared_ptr<uvw::tcp_handle> tcp_handle;

    ConnectionState state;

    Connection(std::shared_ptr<uvw::tcp_handle> tcp_handle)
        : tcp_handle(tcp_handle)
        , state(ConnectionState::Handshake)
    {
    }
};

void handle_end(const uvw::end_event &event, uvw::tcp_handle &client);
void handle_data(const uvw::data_event &event, uvw::tcp_handle &);
