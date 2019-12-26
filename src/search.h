// Created by: WestleyR
// email: westleyr@nym.hush.com
// Date: Dec 25, 2019
// https://github.com/WestleyR/gpack
// version-1.0.0
//
// The Clear BSD License
//
// Copyright (c) 2019 WestleyR
// All rights reserved.
//
// This software is licensed under a Clear BSD License.
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
#include "path-join/path-join.h"

int search_pkg(const char* pat, int print);

#endif // INCLUDE_SEARCH_H

// vim: tabstop=2 shiftwidth=2 expandtab autoindent softtabstop=0
