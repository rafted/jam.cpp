#pragma once

#include <memory>
#include <uvw.hpp>

class Connection
{
private:
    typedef std::shared_ptr<uvw::tcp_handle> TcpHandle;

public:
    TcpHandle tcp_handle;

    Connection(TcpHandle tcp_handle)
        : tcp_handle(tcp_handle)
    {
    }
};

void handle_end(const uvw::end_event &, uvw::tcp_handle &client);
void handle_data(const uvw::data_event &, uvw::tcp_handle &);
