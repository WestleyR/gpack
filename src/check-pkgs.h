//
//  check-pkg.h
//  gpack - https://github.com/WestleyR/gpack
//
// Created by WestleyR on Apr 21, 2020
// Source code: https://github.com/WestleyR/gpack
//
// Copyright (c) 2020-2021 WestleyR. All rights reserved.
// This software is licensed under a BSD 3-Clause Clear License.
// Consult the LICENSE file that came with this software regarding
// your rights to distribute this software.
//

#ifndef CHECK_PKG_H
#define CHECK_PKG_H

#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"
#include "logger/logger.h"

int check_installed_pkg();

#endif // CHECK_PKG_H

// vim: tabstop=2 shiftwidth=2 expandtab autoindent softtabstop=0
