// Created by: WestleyR
// Email: westleyr@nym.hush.com
// Url: https://github.com/WestleyR/gpack
// Last modified date: 2020-12-31
//
// This file is licensed under the terms of
//
// The Clear BSD License
//
// Copyright (c) 2019-2020 WestleyR
// All rights reserved.
//
// This software is licensed under a Clear BSD License.
//


//#define INI_IMPLEMENTATION
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

// vim: tabstop=2 shiftwidth=2 expandtab autoindent softtabstop=0
