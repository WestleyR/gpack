// Created by: WestleyR
// Email: westleyr@nym.hush.com
// Url: https://github.com/WestleyR/gpack
// Last modified date: 2020-09-30
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

#ifndef INCLUDE_LIST_H
#define INCLUDE_LIST_H

#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"
#include "path-join/path-join.h"
#include "logger/logger.h"
#include "ssum/ssum.1.h"
#include "list-files-utils/color.h"

int list_packages();

#endif // INCLUDE_LIST_H

// vim: tabstop=2 shiftwidth=2 expandtab autoindent softtabstop=0
