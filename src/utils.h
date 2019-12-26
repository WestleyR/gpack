// Created by: WestleyR
// email: westleyr@nym.hush.com
// Date: Dec 25, 2019
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

#ifndef INCLUDE_UTILS_GPACK_H
#define INCLUDE_UTILS_GPACK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "path-join/path-join.h"
#include "logger/logger.h"

char* get_installed_pkg_version(const char* usr_pkg, const char* pkg);
char* get_installer();
char* get_package_dir();
char* get_update_script();
char* get_search_script();
char* get_upgrade_script();
char* get_package_prefix();
char* get_bin();
char* get_lib_dir();
char* get_include_dir();

#endif // INCLUDE_UTILS_GPACK_H

// vim: tabstop=2 shiftwidth=2 expandtab autoindent softtabstop=0
