#include "network/connection.h"
#include "network/packet/container.h"
#include "network/packet/packet.h"
#include "network/protocol/implementations/proto_47.h"
#include "network/server.h"
#include "spdlog/spdlog.h"

using namespace network;
using namespace network::packet;

void network::handle_packet(std::shared_ptr<Connection> connection, PacketContainer container, Packet *packet)
{

    switch (connection->state)
    {
    case Handshake:
        switch (container.id)
        {
        case 0:
            proto_47::handshaking::serverbound::HandshakePacket *pkt = static_cast<proto_47::handshaking::serverbound::HandshakePacket *>(packet);

            // switch connection->state
            switch (pkt->next_state)
            {
            case 1:
                connection->state = ConnectionState::Status;
                break;
            case 2:
                connection->state = ConnectionState::Play;
                break;
            default:
                spdlog::debug("invalid next_state value: {}", pkt->next_state);
                break;
            }
        }
    case Status:
    case Login:
    case Play:
    case Closed:
        break;
    }
}

void network::handle_end(const uvw::end_event &, uvw::tcp_handle &client_handle)
{
    std::shared_ptr<Connection> connection = client_handle.data<Connection>();

    spdlog::info("Closed connection from {}:{}", client_handle.sock().ip, client_handle.sock().port);
}

void network::handle_data(const uvw::data_event &event, uvw::tcp_handle &client_handle)
{
    auto server = client_handle.parent().data<Server>();

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

    auto pkt_constructor = server->packet_registry.get(connection->state, Serverbound, container.id);

    if (!pkt_constructor.has_value())
    {
        spdlog::debug("incorrect packet received (Packet ID: {})", container.id);
        return;
    }

    Packet *packet = pkt_constructor.value()();

    packet->decode(container);

    const std::type_info &packet_type = typeid(*packet);

    spdlog::debug("Packet Received (Connection State: {}, Data Length: {}, Packet Length: {}, Packet ID: {}, Packet Type: {})",
        state,
        connection->buffer.size(),
        container.length,
        container.id,
        packet_type.name());

    handle_packet(connection, container, packet);

    // delete packet;
}
