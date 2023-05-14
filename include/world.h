#include <memory>
#include <string>

enum WorldType
{
    Normal,
    Nether,
    End
};

class World
{
public:
    std::string name;
    WorldType type;

public:
    World(std::string name, WorldType type)
        : name { name }
        , type { type }
    {
    }
};

class Location
{
public:
    double x, y, z;
    std::shared_ptr<World> world;

public:
    Location(double x, double y, double z, std::shared_ptr<World> world)
        : x { x }
        , y { y }
        , z { z }
        , world { world }
    {
    }
};
