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

#ifndef INCLUDE_REMOVE_PKG_H
#define INCLUDE_REMOVE_PKG_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

#include "catpath.h"
#include "logger/logger.h"
#include "autoclean.h"

int remove_pkg(const char *pkg);

#endif // INCLUDE_REMOVE_PKG_H

// vim: tabstop=2 shiftwidth=2 expandtab autoindent softtabstop=0
