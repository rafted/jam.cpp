#include "network/connection.h"
#include "network/packet/container.h"
#include "network/packet/packet.h"
#include "network/server.h"
#include "spdlog/spdlog.h"

using namespace network;
using namespace network::packet;

void network::handle_end(const uvw::end_event &, uvw::tcp_handle &client_handle)
{
    std::shared_ptr<Connection> connection = client_handle.data<Connection>();

    spdlog::info("Closed connection from {}:{}", client_handle.sock().ip, client_handle.sock().port);
}

void network::handle_data(const uvw::data_event &event, uvw::tcp_handle &client_handle)
{
    std::shared_ptr<Connection> connection = client_handle.data<Connection>();

    spdlog::debug("Received Data");

    {
        // insert the data into the connection's buffer
        const std::unique_ptr<char[]> &data_ptr = event.data;

        std::vector<char> temp(data_ptr.get(), data_ptr.get() + event.length);
        connection->buffer.insert(connection->buffer.end(), temp.begin(), temp.end());
    }

    // read packet container
    auto container = PacketContainer::read_packet(connection->buffer);

    auto state = static_cast<int>(connection->state);

    auto server = client_handle.parent().data<Server>();

    Packet *packet = server->packet_registry.get(connection->state, Serverbound, container.id)();
    packet->decode(container);

    const std::type_info &packet_type = typeid(*packet);

    spdlog::debug("Packet Received (Connection State: {}, Packet Length: {}, Packet ID: {}, Packet Type: {})",
        state,
        container.length,
        container.id,
        packet_type.name());

    // delete packet;
}
