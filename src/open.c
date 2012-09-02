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
#include <stdarg.h>
#include <malloc.h>

#include "open.h"

void enforcer ( const char * pathname ) {
    const char * to_check = "/tmp/";
    int len = strlen(to_check);
    char * leading = malloc(sizeof(char) * len);
    strncpy(leading, pathname, len);
    if ( strcmp(to_check, leading) == 0 ) {
        printf("tmperamental: caught a write to /tmp.\n");
    }
}

int open ( const char * pathname, int flags, ... ) {
    enforcer( pathname );

    va_list v;
    va_start(v, flags);
    mode_t mode = va_arg(v, mode_t);
    va_end(v);
    if ( mode ) {
        int (*orig_addr)(const char *, int, mode_t) = dlsym(RTLD_NEXT, "open");
        return orig_addr(pathname, flags, mode);
    } else {
        int (*orig_addr)(const char *, int) = dlsym(RTLD_NEXT, "open");
        return orig_addr(pathname, flags);
    }
}

int creat ( const char *pathname, mode_t mode ) {
    enforcer( pathname );

    int (*orig_addr)(const char *, mode_t) = dlsym(RTLD_NEXT, "creat");
    return orig_addr(pathname, mode);
}

FILE * fopen ( const char * path, const char *mode ) {
    enforcer( path );

    FILE * (*orig_addr)(const char *, const char *) = dlsym(RTLD_NEXT, "fopen");
    return orig_addr(path, mode);
}

FILE * freopen ( const char *path, const char *mode, FILE * stream ) {
    enforcer( path );

    FILE * (*orig_addr)(const char *, const char *, FILE *)
        = dlsym(RTLD_NEXT, "freopen");
    return orig_addr(path, mode, stream);
}
