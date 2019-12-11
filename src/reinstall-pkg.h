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

#ifndef INCLUDE_REINSTALL_PKG_H
#define INCLUDE_REINSTALL_PKG_H

#include <stdlib.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "remove-pkg.h"
#include "install-pkg.h"
#include "logger/logger.h"

int reinstall_pkg(const char* pkg);

#endif // INCLUDE_REINSTALL_PKG_H

// vim: tabstop=2 shiftwidth=2 expandtab autoindent softtabstop=0
