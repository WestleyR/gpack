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


#include "cache.h"

char* get_cachepath_for_sha(const char* sha) {
  const char* home_dir = getenv("HOME");
  char* cache_path = path_join(home_dir, ".cache/gpack.cache/packages/tarballs");

  // Create the directory
  // TODO: use C calls
  char mkdir_cmd[200];
  mkdir_cmd[0] = '\0';
  sprintf(mkdir_cmd, "mkdir -p %s", cache_path);
  if (system(mkdir_cmd) != 0) {
    print_errorf("mkdir command failed\n");
    return NULL;
  }

  cache_path = path_join(cache_path, sha);

  return strcat(cache_path, ".tar.gz");
}

int does_cache_path_exist_and_ok(const char* cache_path, const char* checksum) {
  FILE* fp_check = fopen(cache_path, "rb");
  if (fp_check == NULL) {
    // Error opening or does not exist
    return -1;
  }

  unsigned int file_checksum = crc32_file(fp_check, SSUM_BLOCK_SIZE);
  unsigned int verify_checksum = hexstr_int(checksum);

  print_debugf("FILE_CHECKSUM:   %u\n", file_checksum);
  print_debugf("VERIFY_CHECKSUM: %u\n", verify_checksum);

  if (file_checksum != verify_checksum) {
    // Checksum missmatch
    print_warningf("Checksum missmatch.\n");
    print_warningf("Invalid checksum, cannot ensure data...\n");
  }

  fclose(fp_check);

  return 0;
}

// vim: tabstop=2 shiftwidth=2 expandtab autoindent softtabstop=0

