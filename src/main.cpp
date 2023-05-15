#include "../include/entity.h"
#include "../include/network/server.h"
#include "../include/world.h"
#include <entt/entt.hpp>
#include <exception>
#include <memory>
#include <spdlog/spdlog.h>
#include <uvw.hpp>

int main()
{
    spdlog::info("Starting Jam");

    // entt::registry registry;
    //
    // // create test world
    // const auto world = World("default", WorldType::Normal);
    // const auto world_ptr = std::make_shared<World>(world);
    //
    // // create test entity
    // const auto entity = registry.create();
    //
    // // add basic components to test entity
    // registry.emplace<EntityType>(entity, EntityType::Player);
    // registry.emplace<Location>(entity, 0, 0, 0, world_ptr);
    // registry.emplace<Alive>(entity, 20, 20);

    // create uv loop
    auto loop = uvw::loop::get_default();

    Server server(loop, "0.0.0.0", 25565);
    server.start();

    // run event
    loop->run();
}
