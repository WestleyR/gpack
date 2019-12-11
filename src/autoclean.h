// Created by: WestleyR
// email: westleyr@nym.hush.com
// Date: Dec 8, 2019
// https://github.com/WestleyR/gpack
// version-1.0.2
//
// The Clear BSD License
//
// Copyright (c) 2019 WestleyR
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

#include "list-files-utils/find_link.h"
#include "logger/logger.h"

int autoclean();

#endif // AUTOCLEAN_H

// vim: tabstop=2 shiftwidth=2 expandtab autoindent softtabstop=0
