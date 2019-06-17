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

#include <stdio.h>
#include <stdarg.h>

void set_verbose(int);
void set_debug(int);

void print_verbosef(const char*, ...);
void print_debugf(const char*, ...);
void print_errorf(const char*, ...);
void print_warningf(const char*, ...);

//
// End logger.h
//
