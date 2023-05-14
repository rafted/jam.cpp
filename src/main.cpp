#include "../include/entity.h"
#include "../include/world.h"
#include <entt/entt.hpp>
#include <memory>
#include <spdlog/spdlog.h>

int main()
{
    spdlog::info("Starting Jam");

    entt::registry registry;

    // create test world
    const auto world = World("default", WorldType::Normal);
    const auto world_ptr = std::make_shared<World>(world);

    // create test entity
    const auto entity = registry.create();

    // add basic components to test entity
    registry.emplace<EntityType>(entity, EntityType::Player);
    registry.emplace<Location>(entity, 0, 0, 0, world_ptr);
    registry.emplace<Alive>(entity, 20, 20);

    return 0;
}
