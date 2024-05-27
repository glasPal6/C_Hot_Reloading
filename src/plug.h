#ifndef PLUG_H
#define PLUG_H

#include <stddef.h>

#define LIST_OF_PLUGS \
    PLUG(plug_init, void, void) \
    PLUG(plug_destroy, void, void) \
    PLUG(plug_pre_reload, void*, void) \
    PLUG(plug_post_reload, void, void *state) \
    PLUG(plug_update, void, void)

#define PLUG(func, ret, ...) typedef ret (func##_t)(__VA_ARGS__);
LIST_OF_PLUGS
#undef PLUG

#endif // !PLUG_H
