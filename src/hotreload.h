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
