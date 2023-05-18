#include <cstdint>
#include <vector>

struct PacketContainer {
  int32_t length;
  int32_t id;
  std::vector<unsigned char> data;
};
