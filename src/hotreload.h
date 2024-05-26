#ifndef HOTRELOAD_H
#define HOTRELOAD_H

#include <stdbool.h>

#include "plug.h"

#ifdef HOTRELOAD
    #define PLUG(name, ...) extern name##_t *name;
    LIST_OF_PLUGS
    #undef PLUG
    bool reload_libplug();
#else
    #define PLUG(name, ...) name##_t name;
    LIST_OF_PLUGS
    #undef PLUG
    #define reload_libplug() true
#endif // HOTRELOAD

#endif  // HOTRELOAD_H
