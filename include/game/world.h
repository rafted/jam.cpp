#pragma once

#include <memory>
#include <string>

namespace game
{
    namespace world
    {
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

            World(const std::string name, WorldType type)
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
    }
}
