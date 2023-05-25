#include "network/connection.h"
#include "network/container.h"
#include "network/protocol/encoding/varnums.h"
#include "network/protocol/packet.h"
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

    spdlog::debug("Received Data");

    // insert the data into the connection's buffer
    const std::unique_ptr<char[]> &data_ptr = event.data;

    std::vector<char> temp(data_ptr.get(), data_ptr.get() + event.length);
    connection->buffer.insert(connection->buffer.end(), temp.begin(), temp.end());

    {
        // read packet container
        auto container = PacketContainer::read_packet(connection->buffer);

        auto state = static_cast<int>(connection->state);
        spdlog::debug("Packet Received (Connection State: {}, Packet Length: {}, Packet ID: {})", state, container.length, container.id);

        // get encoder & decoder
        auto server = client_handle.parent().data<Server>();
        auto entry = server->packet_registry.get(connection->state, Serverbound, container.id);

        // decode packet by its type
        const void *packet = nullptr;

        packet = reinterpret_cast<const void *>(entry.constructor());
        // TODO: decode using entry.decode

        spdlog::debug("packet type: {}", typeid(packet).name());
    }
}
