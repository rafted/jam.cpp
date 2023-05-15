#pragma once

#include <memory>
#include <uvw.hpp>

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
private:
    typedef std::shared_ptr<uvw::tcp_handle> TcpHandle;

public:
    TcpHandle tcp_handle;

    ConnectionState state;

    Connection(TcpHandle tcp_handle)
        : tcp_handle(tcp_handle)
        , state(ConnectionState::Handshake)
    {
    }
};

void handle_end(const uvw::end_event &, uvw::tcp_handle &client);
void handle_data(const uvw::data_event &, uvw::tcp_handle &);
