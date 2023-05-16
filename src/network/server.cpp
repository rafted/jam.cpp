#include "network/server.h"
#include "network/connection.h"
#include <memory>
#include <spdlog/spdlog.h>
#include <uvw/stream.h>

// std::shared_ptr<Server> Server::instance;
//
// std::shared_ptr<Connection> Server::find_connection_from_handle(uvw::tcp_handle *handle)
// {
//     auto it = handle_connection_map.find(handle);
//
//     if (it != handle_connection_map.end())
//     {
//         return it->second;
//     }
//
//     return std::shared_ptr<Connection>(nullptr);
// }

void handle_error(const uvw::error_event &error, uvw::tcp_handle &)
{
    spdlog::error(error.what());
}

void handle_listen(const uvw::listen_event &, uvw::tcp_handle &server_tcp_handle)
{
    // create tcp handle resource for incoming connection
    std::shared_ptr<uvw::tcp_handle> client_tcp_handle = server_tcp_handle.parent().resource<uvw::tcp_handle>();

    Connection connection(client_tcp_handle);

    // register handlers
    client_tcp_handle->on<uvw::end_event>(handle_end);
    client_tcp_handle->on<uvw::data_event>(handle_data);

    spdlog::debug("Registered handlers");

    // finally accept connection
    server_tcp_handle.accept(*client_tcp_handle);

    // dependency injection -- inject Connection into the tcp_handle of the connection
    client_tcp_handle->data(std::make_shared<Connection>(connection));

    auto sock = client_tcp_handle->sock();
    spdlog::info("Accepted connection from {}:{}", sock.ip, sock.port);
}

void Server::start()
{
    // create tcp handle resource
    this->tcp_handle = this->loop->resource<uvw::tcp_handle>();

    // register handlers
    this->tcp_handle->on<uvw::error_event>(handle_error);
    this->tcp_handle->on<uvw::listen_event>(handle_listen);

    // dependency injection -- inject Server into the tcp_handle of the server
    this->tcp_handle->data(std::make_shared<Server>(this));

    // bind the server
    this->tcp_handle->bind(host, port);
    this->tcp_handle->listen();

    spdlog::info("Listening on {}:{}", host, port);
}
