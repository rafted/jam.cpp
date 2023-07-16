#pragma once

#include <memory>
#include <string>

namespace game
{
    namespace world
    {
        enum Environment
        {
            Normal,
            Nether,
            End
        };

        class World
        {
        public:
            std::string name;
            Environment environment;

            World(const std::string name, Environment environment)
                : name { name }
                , environment { environment }
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
