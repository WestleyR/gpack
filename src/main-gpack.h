// Created by: WestleyR
// Email: westleyr@nym.hush.com
// Url: https://github.com/WestleyR/gpack
// Last modified date: 2021-01-03
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

#include "logger/logger.h"

#define GPACK_VERSION "v1.0.0.b8, 2020-12-03"

#endif // INCLUDE_MAIN_H

// vim: tabstop=2 shiftwidth=2 expandtab autoindent softtabstop=0
