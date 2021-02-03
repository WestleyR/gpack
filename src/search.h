//
//  search.h
//  gpack - https://github.com/WestleyR/gpack
//
// Created by WestleyR on Dec 25, 2019
// Source code: https://github.com/WestleyR/gpack
//
// Copyright (c) 2019-2021 WestleyR. All rights reserved.
// This software is licensed under a BSD 3-Clause Clear License.
// Consult the LICENSE file that came with this software regarding
// your rights to distribute this software.
//

#ifndef INCLUDE_SEARCH_H
#define INCLUDE_SEARCH_H

#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <grp.h>

#include "utils.h"

#include "logger/logger.h"

int search_pkg(const char* pat, int print);

#endif // INCLUDE_SEARCH_H

// vim: tabstop=2 shiftwidth=2 expandtab autoindent softtabstop=0
