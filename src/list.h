//
//  list.h
//  gpack - https://github.com/WestleyR/gpack
//
// Created by WestleyR on Nov 28, 2019
// Source code: https://github.com/WestleyR/gpack
//
// Copyright (c) 2019-2021 WestleyR. All rights reserved.
// This software is licensed under a BSD 3-Clause Clear License.
// Consult the LICENSE file that came with this software regarding
// your rights to distribute this software.
//

#ifndef INCLUDE_LIST_H
#define INCLUDE_LIST_H

#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "catpath.h"
#include "utils.h"
#include "logger/logger.h"
#include "ssum/ssum.1.h"
#include "list-files-utils/color.h"
#include "repo-parser.h"

int list_packages();

#endif // INCLUDE_LIST_H

// vim: tabstop=2 shiftwidth=2 expandtab autoindent softtabstop=0
