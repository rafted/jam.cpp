#include <memory>
#include <string>

#pragma once

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

struct Location
{
    double x, y, z;
    std::shared_ptr<World> world;
};
