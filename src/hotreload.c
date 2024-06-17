#include <dlfcn.h>
#include <stdbool.h>

#include "plug.h"
#include "raylib.h"

const char *libplug_path = "libplug.so";
void *libplug = NULL;

#define PLUG(func, ...) func##_t *func = NULL;
LIST_OF_PLUGS
#undef PLUG

bool reload_libplug(void) {
    if (libplug != NULL) {
        dlclose(libplug);
    }

    libplug = dlopen(libplug_path, RTLD_NOW);
    if (libplug == NULL) {
        TraceLog(LOG_ERROR, "%s\n", dlerror());
        return false;
    }

#define PLUG(func, ...)                                                        \
    func = dlsym(libplug, #func);                                              \
    if (func == NULL) {                                                        \
        TraceLog(LOG_ERROR, "%s\n", dlerror());                                \
        return false;                                                          \
    }
    LIST_OF_PLUGS
#undef PLUG

    return true;
}

bool unload_libplug(void) {
    if (libplug != NULL) {
        dlclose(libplug);
        libplug = NULL;
    }
    return true;
}
