#include "network/container.h"

class Packet {
  virtual PacketContainer encode();

  virtual void decode(PacketContainer container);
};
