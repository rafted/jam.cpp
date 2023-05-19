#pragma once

#include "network/container.h"

class Packet
{
public:
    virtual PacketContainer encode() = 0;

    virtual void decode(PacketContainer container) = 0;
};
