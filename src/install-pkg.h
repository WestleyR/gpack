// Created by: WestleyR
// Email: westleyr@nym.hush.com
// Url: https://github.com/WestleyR/gpack
// Last modified date: 2020-12-31
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

#ifndef INSTALL_PKG_H
#define INSTALL_PKG_H

#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <libgen.h>

#include "remove-pkg.h"
#include "utils.h"
#include "reader.h"
#include "cache.h"
#include "logger/logger.h"

int install_pkg(const char* pkg, int check_installed, int compile_build, int overide);

#endif // INSTALL_PKG_H

// vim: tabstop=2 shiftwidth=2 expandtab autoindent softtabstop=0
