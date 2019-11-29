// Created by: WestleyR
// email: westleyr@nym.hush.com
// Date: Jun 22, 2019
// https://github.com/WestleyR/gpack
// version-1.0.0
//
// The Clear BSD License
//
// Copyright (c) 2019 WestleyR
// All rights reserved.
//
// This software is licensed under a Clear BSD License.
//

#include <stdlib.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "config.h"
#include "remove-pkg.h"
#include "install-pkg.h"
#include "logger/logger.h"

int reinstall_pkg(const char* pkg);

// vim: tabstop=2 shiftwidth=2 expandtab autoindent softtabstop=0
