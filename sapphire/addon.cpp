#include <thread>
#include <node.h>
#include <uv.h>
#include "surface.h"
#include "rectangle.h"

using namespace v8;

RENGINE_DEFINE_GLOBALS

static rengine::Backend *backend;

void pumpEventLoop(uv_timer_t *t)
{
    backend->processEvents();
}

void InitAll(Local<Object> exports)
{
    std::cerr << "Initializing!" << std::endl;

    Surface::Init(exports);
    Rectangle::Init(exports);

    // Kick off the update timer
    uv_timer_t *event_loop_timer = new uv_timer_t;
    uv_timer_init(uv_default_loop(), event_loop_timer);
    uv_timer_start(event_loop_timer, pumpEventLoop, 1, 1);

    std::cerr << "Timer running!" << std::endl;

    backend = rengine::Backend::get();
    backend->processEvents();
}

NODE_MODULE(addon, InitAll)

