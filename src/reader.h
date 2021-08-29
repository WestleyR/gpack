//
//  reader.h
//  gpack - https://github.com/WestleyR/gpack
//
// Created by WestleyR on 2020-12-31
// Source code: https://github.com/WestleyR/gpack
//
// Copyright (c) 2020-2021 WestleyR. All rights reserved.
// This software is licensed under a BSD 3-Clause Clear License.
// Consult the LICENSE file that came with this software regarding
// your rights to distribute this software.
//

#include "ini.h"

const char* get_macos_binary_url(ini_t* ini_data);
const char* get_x86_64_binary_url(ini_t* ini_data);
const char* get_armv6l_binary_url(ini_t* ini_data);

const char* get_macos_binary_ssum(ini_t* ini_data);
const char* get_x86_64_binary_ssum(ini_t* ini_data);
const char* get_armv6l_binary_ssum(ini_t* ini_data);

const char* get_macos_binary_bin_files(ini_t* ini_data);
const char* get_x86_64_binary_bin_files(ini_t* ini_data);
const char* get_armv6l_binary_bin_files(ini_t* ini_data);

const char* get_package_user_name(ini_t* ini_data);
const char* get_package_name(ini_t* ini_data);
const char* get_package_version(ini_t* ini_data);

//const char* get_package_build_command(ini_t* ini_data);
const char* get_package_build_bin_files(ini_t* ini_data);
const char* get_package_build_url(ini_t* ini_data);
const char* get_package_build_ssum(ini_t* ini_data);

// vim: tabstop=2 shiftwidth=2 expandtab autoindent softtabstop=0
