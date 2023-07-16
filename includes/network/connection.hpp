#pragma once

#include "network/packet/container.hpp"
#include "network/packet/packet.hpp"
#include <memory>
#include <uvw.hpp>
#include <uvw/tcp.h>

using namespace network::packet;

namespace network
{
    enum ConnectionState
    {
        Handshake,
        Status,
        Login,
        Play,
        Closed
    };

    class Connection
    {
    public:
        std::shared_ptr<uvw::tcp_handle> tcp_handle;
        std::vector<char> buffer;

        ConnectionState state;

        Connection(std::shared_ptr<uvw::tcp_handle> tcp_handle)
            : tcp_handle(tcp_handle)
            , state(ConnectionState::Handshake)
        {
        }

        ~Connection()
        {
        }
    };

    void handle_packet(std::shared_ptr<Connection> connection, PacketContainer container, Packet *packet);

    void handle_end(const uvw::end_event &event, uvw::tcp_handle &client);
    void handle_data(const uvw::data_event &event, uvw::tcp_handle &);

}
