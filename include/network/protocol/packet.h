#pragma once

#include "network/container.h"
#include <spdlog/spdlog.h>

class Packet
{
    virtual PacketContainer encode();
};

class PacketPlayLook : public Packet
{
public:
    float pitch;
    float yaw;

    PacketContainer encode() override
    {
        spdlog::debug("encoding PacketPlayLook");
        return PacketContainer {};
    }

    static void decode(PacketContainer container)
    {
        spdlog::debug("decoding PacketPlayLook");
    }
};

class PacketRegistry
{
public:
    template<typename T>
    void emplace(std::function<void(PacketContainer)> decode)
    {
        static_assert(std::is_base_of_v<Packet, T>, "T must derive from Packet");
        packets[typeid(T).hash_code()] = std::make_unique<T>();
        packet_decode[typeid(T).hash_code()] = decode;
    }

    template<typename T>
    std::function<void(PacketContainer)> get() const
    {
        static_assert(std::is_base_of_v<Packet, T>, "T must derive from Packet");
        auto it = packet_decode.find(typeid(T).hash_code());

        return it->second;
    }

private:
    std::unordered_map<size_t, std::unique_ptr<Packet>> packets;
    std::unordered_map<size_t, std::function<void(PacketContainer container)>> packet_decode;
};
