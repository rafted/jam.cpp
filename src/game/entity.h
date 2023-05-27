#pragma once

#include "world.h"
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
