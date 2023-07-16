#pragma once

#include "world.hpp"
#include <memory>

namespace game
{
    namespace entity
    {
        struct Health
        {
            double health;
            double food;
        };

        enum Type
        {
            Player
        };
    }
}
