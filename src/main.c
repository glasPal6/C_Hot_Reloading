#include <stddef.h>
#include <dlfcn.h>
#include <stdbool.h>

#include "raylib.h"
#include "hotreload.h"

int main(void)
{
    if (!reload_libplug()) return 1;

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

    return 0;
}
