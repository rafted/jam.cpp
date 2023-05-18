#include "network/container.h"

class Packet
{
public:
    virtual PacketContainer encode();

    virtual void decode(PacketContainer container);
};
