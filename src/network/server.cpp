#include "../../include/network/server.h"
#include "../../include/network/connection.h"
#include <spdlog/spdlog.h>
#include <uvw/stream.h>

void handle_error(const uvw::error_event &error, uvw::tcp_handle &)
{
    spdlog::error(error.what());
}

void handle_listen(const uvw::listen_event &, uvw::tcp_handle &srv)
{
    // create tcp handle resource for incoming connection
    std::shared_ptr<uvw::tcp_handle> client = srv.parent().resource<uvw::tcp_handle>();

    Connection connection(client);

    // register handlers
    client->on<uvw::end_event>(handle_end);
    client->on<uvw::data_event>(handle_data);

    // finally accept connection
    srv.accept(*client);

    spdlog::info("Accepted a connection from {}", client->sock().ip);
}

void Server::start()
{
    // create tcp handle resource
    this->tcp_handle = this->loop->resource<uvw::tcp_handle>();

    // register handlers
    this->tcp_handle->on<uvw::error_event>(handle_error);
    this->tcp_handle->on<uvw::listen_event>(handle_listen);

    // bind the server
    this->tcp_handle->bind(host, port);
    this->tcp_handle->listen();
}
