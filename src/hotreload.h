#ifndef HOTRELOAD_H
#define HOTRELOAD_H

#include <stdbool.h>

#include "plug.h"

#ifdef HOTRELOAD
#define PLUG(func, ...) extern func##_t *func;
LIST_OF_PLUGS
#undef PLUG
bool reload_libplug(void);
bool unload_libplug(void);
#else
#define PLUG(func, ...) func##_t func;
LIST_OF_PLUGS
#undef PLUG
#define reload_libplug() true
#define unload_libplug() true
#endif /* ifdef  */

#endif /* ifndef HOTRELOAD_H */

#ifdef HOTRELOAD_IMPLEMENTATION

#include <dlfcn.h>
#include <stdbool.h>

#include "plug.h"
#include "raylib.h"

const char *libplug_path = "libplug.so";
void *libplug = NULL;

#define PLUG(func, ...) func##_t *func = NULL;
LIST_OF_PLUGS
#undef PLUG

bool unload_libplug(void) {
    if (libplug != NULL) {
        dlclose(libplug);
        libplug = NULL;
    }
    return true;
}

bool reload_libplug(void) {
    if (!unload_libplug()) {
        return false;
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

#endif
