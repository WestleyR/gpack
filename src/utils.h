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

#ifndef INCLUDE_UTILS_GPACK_H
#define INCLUDE_UTILS_GPACK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "catpath.h"

#include "path-join/path-join.h"
#include "logger/logger.h"

char* get_installdir_for_user_and_version(const char* user_name, const char* name, const char* version);

char* pkg_file_registry_dir();

char* package_install_dir();




char* get_listmap_for_pkg(const char* user_name, const char* pkg);
char* get_installed_pkg_version(const char* usr_pkg, const char* pkg);
char* get_installer();
char* get_update_script();
char* get_search_script();
char* get_upgrade_script();
char* get_bin();
char* get_lib_dir();
char* get_include_dir();
char* get_cmd_checksum_file();

#endif // INCLUDE_UTILS_GPACK_H

// vim: tabstop=2 shiftwidth=2 expandtab autoindent softtabstop=0
