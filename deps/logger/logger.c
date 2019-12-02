// Created by: WestleyR
// email: westleyr@nym.hush.com
// Date: Aug 10, 2019
// https://github.com/WestleyR/logger
// version-1.0.2
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

char* ret_func(const char* func) {
    char *ret;

	ret = (char*) malloc(20);
    

    sprintf(ret, "%s():", func);

    return(ret);
}

void print_log_debugf(const char* func, const char* format, ...) {
    if (debug_print == 0) {
        return;
    }

    printf("%sDEBUG:%s    %-28s  ", CYAN, COLOR_RESET, ret_func(func));
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);

    return;
}

void print_log_errorf(const char* func, const char* format, ...) {
	if (debug_print != 0) {
        fprintf(stderr, "%sERROR:%s    %-28s  ", RED, COLOR_RESET, ret_func(func));
    } else {
        fprintf(stderr, "%sERROR:%s    ", RED, COLOR_RESET);
    }

    // TODO: print to stderr
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);

    return;
}

void print_log_warningf(const char* func, const char* format, ...) {
	if (debug_print != 0) {
        fprintf(stderr, "%sWARNING:%s  %-28s  ", YELLOW, COLOR_RESET, ret_func(func));
    } else {
        fprintf(stderr, "%sWARNING:%s  ", YELLOW, COLOR_RESET);
    }

    // TODO: print to stderr
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);

    return;
}

void print_log_verbosef(const char *func, const char *format, ...) {
    if (verbose_print == 0) {
        return;
    }

    if (debug_print != 0) {
        printf("%sVERBOSE:%s  %-28s  ", MAGENTA, COLOR_RESET, ret_func(func));
    } else {
        printf("%sVERBOSE:%s  ", MAGENTA, COLOR_RESET);
    }
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);

    return;
}

void print_log_infof(const char *func, const char *format, ...) {
    if (debug_print != 0) {
        printf("%sINFO:%s     %-28s  ", BLUE, COLOR_RESET, ret_func(func));
    } else {
        printf("%sINFO:%s     ", BLUE, COLOR_RESET);
    }
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);

    return;
}

//
// End logger.c
//
