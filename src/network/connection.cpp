#include "network/server.h"
#include <memory>
#include <spdlog/spdlog.h>
#include <unordered_map>
#include <uvw/tcp.h>

void network::handle_end(const uvw::end_event &, uvw::tcp_handle &client_handle)
{
    std::shared_ptr<network::Connection> connection = client_handle.data<network::Connection>();

    spdlog::info("Closed connection from {}:{}", client_handle.sock().ip, client_handle.sock().port);
}

void network::handle_data(const uvw::data_event &event, uvw::tcp_handle &client_handle)
{
    std::shared_ptr<network::Connection> connection = client_handle.data<network::Connection>();

    spdlog::debug("Received Data");

    {
        // insert the data into the connection's buffer
        const std::unique_ptr<char[]> &data_ptr = event.data;

        std::vector<char> temp(data_ptr.get(), data_ptr.get() + event.length);
        connection->buffer.insert(connection->buffer.end(), temp.begin(), temp.end());
    }

    {
        // read packet container
        auto container = network::PacketContainer::read_packet(connection->buffer);

        auto state = static_cast<int>(connection->state);
        spdlog::debug("Packet Received (Connection State: {}, Packet Length: {}, Packet ID: {})", state, container.length, container.id);

        // get encoder & decoder
        auto server = client_handle.parent().data<network::Server>();
        auto entry = server->packet_registry.get(connection->state, network::packet::Direction::Serverbound, container.id);

        // decode packet by its type
        const void *packet = nullptr;

        packet = reinterpret_cast<const void *>(entry.constructor());
        // TODO: decode using entry.decode

        spdlog::debug("packet type: {}", typeid(packet).name());
    }
}
