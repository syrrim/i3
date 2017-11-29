/*
 * vim:ts=4:sw=4:expandtab
 *
 * i3bar - an xcb-based status- and ws-bar for i3
 *
 * term.c: Manipulate status as a terminal
 *
 */
#include "common.h"
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdio.h>
#include <stdarg.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <err.h>
#include <ev.h>
#include <yajl/yajl_common.h>
#include <yajl/yajl_parse.h>
#include <yajl/yajl_version.h>
#include <yajl/yajl_gen.h>
#include <paths.h>


struct color_block{
    color_t color;
    size_t width;
};
color_block color_blocks[500];
char line[500];
size_t pos = 0;


