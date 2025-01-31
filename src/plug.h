#ifndef PLUG_H
#define PLUG_H

#include <stddef.h>

#define LIST_OF_PLUGS                                                          \
    PLUG(plug_init, void, void)                                                \
    PLUG(plug_destroy, void, void)                                             \
    PLUG(plug_pre_reload, void *, void)                                        \
    PLUG(plug_post_reload, void, void *state)                                  \
    PLUG(plug_update, void, void)

#define PLUG(func, ret, ...) typedef ret(func##_t)(__VA_ARGS__);
LIST_OF_PLUGS
#undef PLUG

#endif // !PLUG_H

#ifdef PLUG_IMPLEMENTATION

#include <assert.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "raylib.h"

typedef struct {
    Color background;
} Plug;

static Plug *p = NULL;

void plug_init(void) {
    p = malloc(sizeof(*p));
    assert(p != NULL);
    memset(p, 0, sizeof(*p));
    p->background = RED;

    TraceLog(LOG_INFO, "PLUGIN: Initialized plugin");
}

void plug_destroy(void) {
    free(p);

    TraceLog(LOG_INFO, "PLUGIN: Uninitialized plugin");
}

void *plug_pre_reload(void) { return p; }

void plug_post_reload(void *state) { p = state; }

void plug_update(void) {
    BeginDrawing();

    ClearBackground(p->background);
    /*DrawText("Hello, World!", 100, 100, 20, WHITE);*/
    /*DrawText("This is Hot Reloading Working", 100, 150, 15, WHITE);*/

    EndDrawing();
}

#endif
