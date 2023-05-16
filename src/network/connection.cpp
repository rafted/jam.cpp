#include "network/connection.h"
#include "network/server.h"
#include <memory>
#include <spdlog/spdlog.h>
#include <unordered_map>
#include <uvw/tcp.h>

void handle_end(const uvw::end_event &, uvw::tcp_handle &client_handle)
{
    std::shared_ptr<Connection> connection = client_handle.data<Connection>();

    spdlog::info("Closed connection from {}:{}", client_handle.sock().ip, client_handle.sock().port);
}

void handle_data(const uvw::data_event &, uvw::tcp_handle &client_handle)
{
    spdlog::debug("handle_data called");
    // std::shared_ptr<Connection> connection = Server::instance->find_connection_from_handle(std::addressof(client_handle));
}
