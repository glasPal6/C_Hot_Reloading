#include <dlfcn.h>
#include <stdbool.h>

/*#define HOTRELOAD_IMPLEMENTATION*/
#include "hotreload.h"
#include "raylib.h"

int main(void)

{
    if (!reload_libplug())
        return 1;

    plug_init();
    InitWindow(800, 600, "Hot Reloading");

    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_R)) {
            void *state = plug_pre_reload();
            reload_libplug();
            plug_post_reload(state);
        }
        plug_update();
    }

    CloseWindow();
    plug_destroy();

    if (!unload_libplug())
        return 1;

    return 0;
}
