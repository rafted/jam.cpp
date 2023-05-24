#pragma once

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
    static PacketContainer EncodeWrapper(Packet &packet)
    {
        return packet.encode();
    }

    static PacketContainer DecodeWrapper(Packet &packet, PacketContainer container)
    {
        packet.decode(container);
        return container;
    }
};

class PacketRegistry
{
public:
    // typedef std::function<PacketContainer(Packet &)> EncodeFn;
    // typedef std::function<PacketContainer(Packet &, PacketContainer)> DecodeFn;

    typedef PacketContainer (*EncodeFn)(Packet &);
    typedef PacketContainer (*DecodeFn)(Packet &, PacketContainer);

    PacketRegistry() { }

    template<typename T>
    void emplace(Direction direction, int id, EncodeFn encode, DecodeFn decode)
    {
        static_assert(std::is_base_of_v<Packet, T>, "T must derive from Packet");

        packets[std::make_pair(direction, id)] = std::make_pair(encode, decode);
    }

    // template<typename T>
    // std::function<void(PacketContainer)> get() const
    // {
    //     static_assert(std::is_base_of_v<Packet, T>, "T must derive from Packet");
    //     return packet_decode.find(typeid(T).hash_code())->second;
    // }

private:
    std::map<std::pair<Direction, int>, std::pair<EncodeFn, DecodeFn>> packets;
};
