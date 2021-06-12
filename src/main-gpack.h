//
//  main-gpack.h
//  gpack - https://github.com/WestleyR/gpack
//
// Created by WestleyR on Jun 16, 2019
// Source code: https://github.com/WestleyR/gpack
//
// Copyright (c) 2019-2021 WestleyR. All rights reserved.
// This software is licensed under a BSD 3-Clause Clear License.
// Consult the LICENSE file that came with this software regarding
// your rights to distribute this software.
//

#ifndef INCLUDE_MAIN_H
#define INCLUDE_MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <getopt.h>

#include "install-pkg.h"
#include "list.h"
#include "autoclean.h"
#include "update-pkg.h"
#include "upgrade-pkg.h"
#include "remove-pkg.h"
#include "check-pkgs.h"
#include "search.h"
#include "utils.h"
#include "cmd-ensure.h"
#include "config.h"
#include "repo-parser.h"

#include "logger/logger.h"

#define GPACK_VERSION "v1.0.0.b9, 2021-02-01"

#endif // INCLUDE_MAIN_H

// vim: tabstop=2 shiftwidth=2 expandtab autoindent softtabstop=0
