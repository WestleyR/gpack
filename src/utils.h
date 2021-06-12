//
//  utils.h
//  gpack - https://github.com/WestleyR/gpack
//
// Created by WestleyR on Nov 28, 2019
// Source code: https://github.com/WestleyR/gpack
//
// Copyright (c) 2019-2021 WestleyR. All rights reserved.
// This software is licensed under a BSD 3-Clause Clear License.
// Consult the LICENSE file that came with this software regarding
// your rights to distribute this software.
//

#ifndef INCLUDE_UTILS_GPACK_H
#define INCLUDE_UTILS_GPACK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/utsname.h>

#include "catpath.h"
#include "ini.h"
#include "reader.h"
#include "helper.h"

#include "logger/logger.h"

// TODO: add documantation


char* get_repolist_url();

char* get_gpack_arch();

char* get_binary_sha(const char* arch);

char* get_installdir_for_user_and_version(const char* usr_pkg, const char* version);

char* pkg_file_registry_dir();

char* package_install_dir();

char* get_latest_version_for_pkg(const char* user_name, const char* pkg);

char* get_repo_index_file();

char* get_installed_pkg_version(const char* usr_pkg, const char* pkg);
char* get_update_script();
char* get_search_script();
char* get_upgrade_script();
char* get_bin();
char* get_lib_dir();
char* get_include_dir();
char* get_cmd_checksum_file();

#endif // INCLUDE_UTILS_GPACK_H

// vim: tabstop=2 shiftwidth=2 expandtab autoindent softtabstop=0
