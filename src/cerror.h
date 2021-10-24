//
//  errors.h
//  errors - https://github.com/??? (will be a c library)
//
// Created by WestleyR on 2021-08-29
// Source code: https://github.com/WestleyR/gpack
//
// Copyright (c) 2021 WestleyR. All rights reserved.
// This software is licensed under a BSD 3-Clause Clear License.
// Consult the LICENSE file that came with this software regarding
// your rights to distribute this software.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#ifndef CERROR_H__
#define CERROR_H__

typedef struct cerror {
  char* err;
  int len;
  char** stack_trace;
  int stack_len;
  int stack_alloc;
  int empty;
} cerror;

// new_cerror returns a new empty error struct.
cerror new_cerror();

#define error_printf(E, ...) cerror_printf(__FILE__, __func__, __LINE__, E, __VA_ARGS__)

// error_printf appends to the left side of the error message if it already has content.
// Otherwise it will return a allocated error containing the message.
int cerror_printf(const char* file, const char* func, int line, cerror* err, const char* fmt, ...);

int print_stack_trace(cerror err, FILE* stream);

// error_clear resets the error message.
int error_clear(cerror* err);

// iserror returns 1 (true) if err is set.
int iserror(cerror* err);

// noerror should be called when you do not want to check the error
// return of a functions, ie.
//   some_func(noerror(), "arg1");
void* noerror();

#endif // CERROR_H__

// vim: tabstop=2 shiftwidth=2 expandtab autoindent softtabstop=0
