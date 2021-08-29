//
//  upgrade-pkg.h
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

#ifndef INCLUDE_UPGRADE_PKG_H
#define INCLUDE_UPGRADE_PKG_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>

#include "utils.h"
#include "catpath.h"
#include "ini.h"
#include "install-pkg.h"
#include "repo-parser.h"

#include "logger/logger.h"

int upgrade_pkg();

#endif // INCLUDE_UPGRADE_PKG_H

// vim: tabstop=2 shiftwidth=2 expandtab autoindent softtabstop=0
