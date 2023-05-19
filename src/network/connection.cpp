#include "network/connection.h"
#include "network/container.h"
#include "network/protocol/encoding/varnums.h"
#include "network/protocol/proto_47.h"
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

void handle_data(const uvw::data_event &event, uvw::tcp_handle &client_handle)
{
    std::shared_ptr<Connection> connection = client_handle.data<Connection>();

    spdlog::debug("handle_data called");

    // insert the data into the connection's buffer
    const std::unique_ptr<char[]> &data_ptr = event.data;

    std::vector<char> temp(data_ptr.get(), data_ptr.get() + event.length);
    connection->buffer.insert(connection->buffer.end(), temp.begin(), temp.end());

    {
        auto container = PacketContainer::read_packet(connection->buffer);
        proto_47::handshaking::serverbound::HandshakePacket pkt;

        pkt.decode(container);

        spdlog::debug("packet length: {}", container.length);
        spdlog::debug("packet id: {}", container.id);

        spdlog::debug("Protocol Version: {}", pkt.protocol_version);
        spdlog::debug("Server Address: {}", pkt.server_address);
        spdlog::debug("Server Port: {}", pkt.server_port);
        spdlog::debug("Next State: {}", pkt.next_state);
    }
}
