// Created by: WestleyR
// Email: westleyr@nym.hush.com
// Url: https://github.com/WestleyR/gpack
// Last modified date: 2021-01-06
//
// This file is licensed under the terms of
//
// The Clear BSD License
//
// Copyright (c) 2019-2021 WestleyR
// All rights reserved.
//
// This software is licensed under a Clear BSD License.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "catpath.h"
#include "logger/logger.h"
#include "ssum/ssum.1.h"

char* get_cachepath_for_sha(const char* sha);

int does_cache_path_exist_and_ok(const char* cache_path, const char* checksum);

// vim: tabstop=2 shiftwidth=2 expandtab autoindent softtabstop=0
