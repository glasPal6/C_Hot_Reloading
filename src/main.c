#include <stddef.h>
#include <dlfcn.h>
#include <stdio.h>
#include <stdbool.h>

#include "raylib.h"
#include "plug.h"

const char *libplug_path = "libplug.so";
void *libplug = NULL;

bool reload_libplug()
{
    if (libplug != NULL) {
        dlclose(libplug);
    }

    libplug = dlopen(libplug_path, RTLD_NOW);
    if (libplug == NULL) {
        TraceLog(LOG_ERROR, "%s\n", dlerror());
        return false;
    }

    #define PLUG(func, ...) \
        func = dlsym(libplug, #func); \
        if (func == NULL) { \
            TraceLog(LOG_ERROR, "%s\n", dlerror()); \
            return false; \
        }
    LIST_OF_PLUGS
    #undef PLUG

    return true;
}

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
