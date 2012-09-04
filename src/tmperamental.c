/*
 * Copyright (c) 2011 Paul Tagliamonte <paultag@debian.org>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#define _GNU_SOURCE 1
/* This horseshit hack brought to you by the fine folks over at wherever
 * the fuck this came from. This breaks in Cygwin. Not that that really
 * matters in this small case. */

#include <dlfcn.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <malloc.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <execinfo.h>

#include "tmperamental.h"

static int (*orig_open)(const char *, int, ...);
static int (*orig_mkdir)(const char *, mode_t);
static int (*orig_creat)(const char *, mode_t);
static FILE * (*orig_fopen)(const char *, const char *);
static FILE * (*orig_freopen)(const char *, const char *, FILE *);

static void tmperamental_init ( void ) __attribute__((constructor));

static void tmperamental_init ( void ) {
    orig_open = dlsym(RTLD_NEXT, "open");
    orig_mkdir = dlsym(RTLD_NEXT, "mkdir");
    orig_creat = dlsym(RTLD_NEXT, "creat");
    orig_fopen = dlsym(RTLD_NEXT, "fopen");
    orig_freopen = dlsym(RTLD_NEXT, "freopen");
}

#define SIZE (100)
#define FIRST_FRAME (1)
void enforcer ( const char * pathname ) {
    if ( strncmp("/tmp/", pathname, 5) == 0 ) {
        int nframes;
        void *buffer[SIZE];
        fprintf(stderr, "tmperamental: caught a write to /tmp.\n");
        nframes = backtrace(buffer, SIZE);
        if(nframes > FIRST_FRAME)
            backtrace_symbols_fd(buffer+FIRST_FRAME, nframes+FIRST_FRAME, 2);
        abort();
    }
}

int open ( const char * pathname, int flags, ... ) {
    enforcer(pathname);

    va_list v;
    va_start(v, flags);
    if ( flags & O_CREAT ) {
        mode_t mode = va_arg(v, mode_t);
        va_end(v);
        return orig_open(pathname, flags, mode);
    } else {
        va_end(v);
        return orig_open(pathname, flags);
    }
}

int mkdir ( const char *pathname, mode_t mode ) {
    enforcer( pathname );

    return orig_mkdir(pathname, mode);
}

int creat ( const char *pathname, mode_t mode ) {
    enforcer( pathname );

    return orig_creat(pathname, mode);
}

FILE * fopen ( const char * path, const char *mode ) {
    enforcer(path);

    return orig_fopen( path, mode );
}

FILE * freopen ( const char *path, const char *mode, FILE * stream ) {
    enforcer(path);

    return orig_freopen(path, mode, stream);
}
