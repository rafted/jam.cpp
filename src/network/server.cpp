#include "../../include/network/server.h"
#include "../../include/network/connection.h"

void Server::start()
{
    // create tcp handle resource
    this->tcp_handle = this->loop->resource<uvw::tcp_handle>();

    this->tcp_handle->bind(host, port);
    this->tcp_handle->listen();
}
