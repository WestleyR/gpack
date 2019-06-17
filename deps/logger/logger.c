// Created by: WestleyR
// email: westleyr@nym.hush.com
// Date: Jun 16, 2019
// https://github.com/WestleyR/logger
// version-1.0.0
//
// The Clear BSD License
//
// Copyright (c) 2019 WestleyR
// All rights reserved.
//
// This software is licensed under a Clear BSD License.
//

#define COLOR_RESET "\033[0m"
#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define YELLOW "\033[0;33m"
#define BLUE "\033[0;34m"
#define MAGENTA "\033[0;35m"
#define CYAN "\033[0;36m"
#define BOLD "\033[1m"

#include "logger.h"

int verbose_print = 0;
int debug_print = 0;

void set_verbose(int setting) {
    verbose_print = setting;
}

void set_debug(int setting) {
    debug_print = setting;
}

void print_verbosef(const char* restrict format, ...) {
    if (verbose_print == 0) {
        return;
    }

    printf("%sVERBOSE:%s ", MAGENTA, COLOR_RESET);
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);

    return;
}

void print_debugf(const char* restrict format, ...) {
    if (debug_print == 0) {
        return;
    }

    printf("%sDEBUG:  %s ", CYAN, COLOR_RESET);
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);

    return;
}

void print_errorf(const char* restrict format, ...) {
    fprintf(stderr, "%sERROR:%s   ", RED, COLOR_RESET);

    // TODO: print to stderr
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);

    return;
}

void print_warningf(const char* restrict format, ...) {
    fprintf(stderr, "%sWARNING:%s ", YELLOW, COLOR_RESET);

    // TODO: print to stderr
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);

    return;
}

//
// End logger.c
//
