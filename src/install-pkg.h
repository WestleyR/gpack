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

#ifndef INSTALL_PKG_H
#define INSTALL_PKG_H

#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <libgen.h>

#include "catpath.h"
#include "bool.h"
#include "remove-pkg.h"
#include "utils.h"
#include "reader.h"
#include "cache.h"
#include "logger/logger.h"

const static int GPK_INSTALL_OVERIDE = 1;
const static int GPK_INSTALL_COMPILE_BUILD = 2;

const static int GPK_INSTALL_MAX_OPTS = 3; // +1 extra

// The terminator for the options
const static int GPK_OPTS_END = 0;

typedef int gpk_install_opts[];

int install_pkg(const char* pkg, gpk_install_opts opts);

#endif // INSTALL_PKG_H

// vim: tabstop=2 shiftwidth=2 expandtab autoindent softtabstop=0
