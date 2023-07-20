#include "flecs.h"
#include "flecs/addons/cpp/c_types.hpp"
#include "game/entity.hpp"
#include "network/server.hpp"
#include "uvw/timer.h"
#include <spdlog/spdlog.h>
#include <uvw.hpp>

void tick(const uvw::timer_event &, uvw::timer_handle &handle)
{
    auto world = handle.parent().data<flecs::world>();
    world->progress();
}

int main()
{
#ifdef NDEBUG
#else
    spdlog::set_level(spdlog::level::debug);
#endif

    spdlog::info("Starting Jam");
    // initialize ecs
    flecs::world ecs;

    // // add basic components to test entity
    // registry.emplace<EntityType>(entity, EntityType::Player);
    // registry.emplace<Location>(entity, 0, 0, 0, world_ptr);
    // registry.emplace<Alive>(entity, 20, 20);

    // create libuv event loop
    auto loop = uvw::loop::get_default();
    auto timer = loop->resource<uvw::timer_handle>();

    // initialize the server
    network::Properties properties = {
        .host = "0.0.0.0",
        .port = 25565,
        .protocol = 47
    };

    network::Server server(loop, properties);
    server.start();

    // set up timer to run tick loop
    timer->on<uvw::timer_event>(tick);
    timer->start(uvw::timer_handle::time(0), uvw::timer_handle::time(50));

    // run event loop
    loop->run();
}
