#pragma once

#include "network/connection.h"
#include "network/container.h"
#include <functional>
#include <map>
#include <spdlog/spdlog.h>
#include <type_traits>

enum Direction
{
    Serverbound,
    Clientbound
};

class Packet
{
    virtual PacketContainer encode() { }
    virtual void decode(PacketContainer container) { }

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

    template<typename T>
    static Packet *constructor_wrapper()
    {
        static_assert(std::is_base_of_v<Packet, T>, "T must derive from Packet");

        T *newPacket = new T();

        return static_cast<Packet *>(newPacket);
    }
};

typedef PacketContainer (*EncodeFn)(Packet &);
typedef PacketContainer (*DecodeFn)(Packet &, PacketContainer);
typedef Packet *(*ConstructorFn)();

struct PacketRegistryEntry
{
    EncodeFn encode;
    DecodeFn decode;

    ConstructorFn constructor;
};

class PacketRegistry
{
public:
    typedef unsigned long PacketId;

    PacketRegistry() { }

    int make_id(ConnectionState state, Direction direction, int id)
    {
        int stateInt = static_cast<int>(state);
        int directionInt = static_cast<int>(direction);

        // Perform the merging
        return (stateInt << 8) | (directionInt << 4) | id;
    }

    template<typename T>
    void emplace(ConnectionState state, Direction direction, int id, EncodeFn encode, DecodeFn decode)
    {
        static_assert(std::is_base_of_v<Packet, T>, "T must derive from Packet");

        ConstructorFn constructor = []() -> Packet *
        {
            return Packet::constructor_wrapper<T>();
        };

        packets[make_id(state, direction, id)] = PacketRegistryEntry {
            .encode = encode,
            .decode = decode,
            .constructor = constructor
        };

        spdlog::debug("added packet with id {}", make_id(state, direction, id));
        spdlog::debug("length of packets is now {}", packets.size());
    }

    PacketRegistryEntry get(ConnectionState state, Direction direction, int id)
    {
        return packets[make_id(state, direction, id)];
    }

private:
    std::map<unsigned int, PacketRegistryEntry> packets;
};
