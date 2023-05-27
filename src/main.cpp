#include "network/server.h"
#include <spdlog/spdlog.h>
#include <uvw.hpp>

int main()
{
#ifdef NDEBUG
#else
    spdlog::set_level(spdlog::level::debug);
#endif

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

    network::Properties properties = {
        .host = "0.0.0.0",
        .port = 25565,
        .protocol = 47
    };

    network::Server server(loop, properties);
    server.start();

    // run event
    loop->run();
}
