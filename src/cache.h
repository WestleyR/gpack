// Created by: WestleyR
// Email: westleyr@nym.hush.com
// Url: https://github.com/WestleyR/gpack
// Last modified date: 2020-12-31
//
// This file is licensed under the terms of
//
// The Clear BSD License
//
// Copyright (c) 2019-2020 WestleyR
// All rights reserved.
//
// This software is licensed under a Clear BSD License.
//


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "path-join/path-join.h"
#include "logger/logger.h"

char* get_cachepath_for_sha(const char* sha);

int does_cache_path_exist_and_ok(const char* cache_path);

// vim: tabstop=2 shiftwidth=2 expandtab autoindent softtabstop=0
