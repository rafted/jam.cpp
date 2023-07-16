#pragma once

#include "world.hpp"
#include <memory>

namespace game
{
    namespace entity
    {
        struct Alive
        {
            double health;
            double food;
        };

        enum EntityType
        {
            Player
        };
    }
}
