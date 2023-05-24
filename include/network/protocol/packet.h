#pragma once

#include "network/connection.h"
#include "network/container.h"
#include <functional>
#include <map>
#include <spdlog/spdlog.h>

enum Direction
{
    Serverbound,
    Clientbound
};

class Packet
{
    virtual PacketContainer encode();
    virtual void decode(PacketContainer container);

public:
    static PacketContainer encode_wrapper(Packet &packet)
    {
        return packet.encode();
    }

    static PacketContainer decode_wrapper(Packet &packet, PacketContainer container)
    {
        packet.decode(container);
        return container;
    }
};

class PacketRegistry
{
public:
    typedef PacketContainer (*EncodeFn)(Packet &);
    typedef PacketContainer (*DecodeFn)(Packet &, PacketContainer);

    typedef unsigned long PacketId;

    PacketRegistry() { }

    int make_id(ConnectionState state, Direction direction, int id)
    {
        return (state << 8) | (direction << 4) | id;
    }

    template<typename T>
    void emplace(ConnectionState state, Direction direction, int id, EncodeFn encode, DecodeFn decode)
    {
        static_assert(std::is_base_of_v<Packet, T>, "T must derive from Packet");

        packets[make_id(state, direction, id)] = std::make_pair(encode, decode);
    }

    template<typename T>
    std::pair<EncodeFn, DecodeFn> get(ConnectionState state, Direction direction, int id)
    {
        static_assert(std::is_base_of_v<Packet, T>, "T must derive from Packet");

        return packets[make_id(state, direction, id)];
    }

private:
    std::map<unsigned int, std::pair<EncodeFn, DecodeFn>> packets;
};
