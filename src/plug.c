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
    /*DrawText("This is the Hot Reloading plugin working", 100, 150, 15,
     * WHITE);*/

    EndDrawing();
}
