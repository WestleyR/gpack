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


#include "reader.h"
#define INI_IMPLEMENTATION
#include "ini.h"

const char* get_macos_binary_url(ini_t* ini_data) {
  int section = ini_find_section(ini_data, "macOS\0", 0);
  int second_index = ini_find_property(ini_data, section, "TarballURL\0", 0);
  return ini_property_value(ini_data, section, second_index);
}

const char* get_x86_64_binary_url(ini_t* ini_data) {
  int section = ini_find_section(ini_data, "x86_64_linux\0", 0);
  int second_index = ini_find_property(ini_data, section, "TarballURL\0", 0);
  return ini_property_value(ini_data, section, second_index);
}

const char* get_armv6l_binary_url(ini_t* ini_data) {
  int section = ini_find_section(ini_data, "armv6l\0", 0);
  int second_index = ini_find_property(ini_data, section, "TarballURL\0", 0);
  return ini_property_value(ini_data, section, second_index);
}


const char* get_macos_binary_ssum(ini_t* ini_data) {
  int section = ini_find_section(ini_data, "macOS\0", 0);
  int second_index = ini_find_property(ini_data, section, "SSUM\0", 0);
  return ini_property_value(ini_data, section, second_index);
}

const char* get_x86_64_binary_ssum(ini_t* ini_data) {
  int section = ini_find_section(ini_data, "x86_64_linux\0", 0);
  int second_index = ini_find_property(ini_data, section, "SSUM\0", 0);
  return ini_property_value(ini_data, section, second_index);
}

const char* get_armv6l_binary_ssum(ini_t* ini_data) {
  int section = ini_find_section(ini_data, "armv6l\0", 0);
  int second_index = ini_find_property(ini_data, section, "SSUM\0", 0);
  return ini_property_value(ini_data, section, second_index);
}


const char* get_macos_binary_bin_files(ini_t* ini_data) {
  int section = ini_find_section(ini_data, "macOS\0", 0);
  int second_index = ini_find_property(ini_data, section, "BIN_FILES\0", 0);
  return ini_property_value(ini_data, section, second_index);
}

const char* get_x86_64_binary_bin_files(ini_t* ini_data) {
  int section = ini_find_section(ini_data, "x86_64_linux\0", 0);
  int second_index = ini_find_property(ini_data, section, "BIN_FILES\0", 0);
  return ini_property_value(ini_data, section, second_index);
}

const char* get_armv6l_binary_bin_files(ini_t* ini_data) {
  int section = ini_find_section(ini_data, "armv6l\0", 0);
  int second_index = ini_find_property(ini_data, section, "BIN_FILES\0", 0);
  return ini_property_value(ini_data, section, second_index);
}


// User name
const char* get_package_user_name(ini_t* ini_data) {
  int second_index = ini_find_property(ini_data, INI_GLOBAL_SECTION, "UserName\0", 0);
  return ini_property_value(ini_data, INI_GLOBAL_SECTION, second_index);
}

// Package name
const char* get_package_name(ini_t* ini_data) {
  int second_index = ini_find_property(ini_data, INI_GLOBAL_SECTION, "Name\0", 0);
  return ini_property_value(ini_data, INI_GLOBAL_SECTION, second_index);
}

// Package version
const char* get_package_version(ini_t* ini_data) {
  int second_index = ini_find_property(ini_data, INI_GLOBAL_SECTION, "Version\0", 0);
  return ini_property_value(ini_data, INI_GLOBAL_SECTION, second_index);
}

// Package build command
const char* get_package_build_command(ini_t* ini_data) {
  int section = ini_find_section(ini_data, "build\0", 0);
  int second_index = ini_find_property(ini_data, section, "BuildCmd\0", 0);
  return ini_property_value(ini_data, section, second_index);
}

// Package build bin files
const char* get_package_build_bin_files(ini_t* ini_data) {
  int section = ini_find_section(ini_data, "build\0", 0);
  int second_index = ini_find_property(ini_data, section, "BIN_FILES\0", 0);
  return ini_property_value(ini_data, section, second_index);
}

// Package build url
const char* get_package_build_url(ini_t* ini_data) {
  int section = ini_find_section(ini_data, "build\0", 0);
  int second_index = ini_find_property(ini_data, section, "TarballURL\0", 0);
  return ini_property_value(ini_data, section, second_index);
}

// Package build ssum
const char* get_package_build_ssum(ini_t* ini_data) {
  int section = ini_find_section(ini_data, "build\0", 0);
  int second_index = ini_find_property(ini_data, section, "SSUM\0", 0);
  return ini_property_value(ini_data, section, second_index);
}





// vim: tabstop=2 shiftwidth=2 expandtab autoindent softtabstop=0
