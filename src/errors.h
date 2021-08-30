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

#define error char*

// error_printf appends to the left side of the error message if it already has content.
// Otherwise it will return a allocated error containing the message.
int error_printf(error* err, const char* fmt, ...);

// error_clear resets the error message.
int error_clear(error* err);

// iserror returns 1 (true) if err is set.
int iserror(error* err);

// noerror should be called when you do not want to check the error
// return of a functions, ie.
//   some_func(noerror(), "arg1");
error* noerror();

// vim: tabstop=2 shiftwidth=2 expandtab autoindent softtabstop=0
