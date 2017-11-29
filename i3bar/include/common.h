/*
 * vim:ts=4:sw=4:expandtab
 *
 * i3bar - an xcb-based status- and ws-bar for i3
 * © 2010 Axel Wagner and contributors (see also: LICENSE)
 *
 */
#pragma once

#include <config.h>

#include <stdbool.h>
#include <xcb/xcb.h>
#include <xcb/xproto.h>
#include "libi3.h"
#include "queue.h"

typedef struct rect_t rect;

struct ev_loop *main_loop;

struct rect_t {
    int x;
    int y;
    int w;
    int h;
};

typedef enum {
    /* First value to make it the default. */
    ALIGN_LEFT,
    ALIGN_CENTER,
    ALIGN_RIGHT
} blockalign_t;

/* This data structure describes the way a status block should be rendered. These
 * variables are updated each time the statusline is re-rendered. */
struct status_block_render_desc {
    uint32_t width;
    uint32_t x_offset;
    uint32_t x_append;
};

#define STATUS_BLOCK_MAX_FILL() (1<<16);

/* This data structure represents one JSON dictionary, multiple of these make
 * up one status line. */
struct status_block {
    i3String *full_text;

    char *color;
    char *background;
    char *border;

    /* If set, the number of pixels away from the left to position the block
     * */
    uint32_t pos;
    /* The number of chars the block wants to take up. Set to zero to have it be
     * variable.  */
    uint32_t width;
    /* The number of pixels allocated to the block on screen */
    uint32_t actual_width;

    /* Whether the block should be drawn above, rather than below, it's
     * successor */
    bool above;

    blockalign_t align;

    /* Optionally, the background of the block can be partially filled to
     * demonstrate a percentage. */
    uint32_t fill; 
    char *fill_color;


    bool urgent;
    bool no_separator;
    bool pango_markup;

    /* Optional */
    char *name;
    char *instance;

    TAILQ_ENTRY(status_block)
    blocks;
};

TAILQ_HEAD(statusline_head, status_block)
statusline_head;

#include "child.h"
#include "ipc.h"
#include "outputs.h"
#include "util.h"
#include "workspaces.h"
#include "mode.h"
#include "trayclients.h"
#include "xcb.h"
#include "configuration.h"
#include "libi3.h"
#include "parse_json_header.h"
