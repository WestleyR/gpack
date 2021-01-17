// Created by: WestleyR
// Email: westleyr@nym.hush.com
// Url: https://github.com/WestleyR/gpack
// Last modified date: 2021-01-16
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

#ifndef AUTOCLEAN_H
#define AUTOCLEAN_H

#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <grp.h>

#include "utils.h"
#include "catpath.h"
#include "list-files-utils/find_link.h"
#include "logger/logger.h"

int helper_autoclean(int dry_run);
int autoclean(const char* clean_dir, int dry_run);

#endif // AUTOCLEAN_H

// vim: tabstop=2 shiftwidth=2 expandtab autoindent softtabstop=0
