// Created by: WestleyR
// email: westleyr@nym.hush.com
// Date: Dec 8, 2019
// https://github.com/WestleyR/gpack
// version-1.0.1
//
// The Clear BSD License
//
// Copyright (c) 2019 WestleyR
// All rights reserved.
//
// This software is licensed under a Clear BSD License.
//

#ifndef INCLUDE_UPGRADE_PKG_H
#define INCLUDE_UPGRADE_PKG_H

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>

#include "utils.h"
#include "reinstall-pkg.h"
#include "logger/logger.h"

int upgrade_pkg(int compile_build);

#endif // INCLUDE_UPGRADE_PKG_H

// vim: tabstop=2 shiftwidth=2 expandtab autoindent softtabstop=0
