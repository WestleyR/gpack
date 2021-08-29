//
//  reader.c
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

#include "reader.h"

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

// Will not support building
//// Package build command
//const char* get_package_build_command(ini_t* ini_data) {
//  int section = ini_find_section(ini_data, "build\0", 0);
//  int second_index = ini_find_property(ini_data, section, "BuildCmd\0", 0);
//  return ini_property_value(ini_data, section, second_index);
//}

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

// TODO: take a context logger to log error messages.
//ini_t* get_repolist_ini() {
//  print_debugf("funcall\n");
//
//  FILE* fp = fopen(pkg_file, "r");
//  if (fp == NULL) {
//    fprintf(stderr, "Failed to open file: %s\n", pkg_file);
//    free(pkg_file);
//    return NULL;
//  }
//
//  // Load the package file into memory
//  fseek(fp, 0, SEEK_END);
//  int size = ftell(fp);
//  fseek(fp, 0, SEEK_SET);
//  char* data = (char*) malloc(size + 1);
//  fread(data, 1, size, fp);
//  data[size] = '\0';
//  fclose(fp);
//
//  ini_t* ini = ini_load(data, NULL);
//  free(data);
//
//  return ini;
//}

// vim: tabstop=2 shiftwidth=2 expandtab autoindent softtabstop=0
