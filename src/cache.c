//
//  cache.c
//  gpack - https://github.com/WestleyR/gpack
//
// Created by WestleyR on Dec 31, 2020
// Source code: https://github.com/WestleyR/gpack
//
// Copyright (c) 2020-2021 WestleyR. All rights reserved.
// This software is licensed under a BSD 3-Clause Clear License.
// Consult the LICENSE file that came with this software regarding
// your rights to distribute this software.
//

#include "cache.h"

// Need to free() the return string when done with it.
char* get_cachepath_for_sha(const char* sha) {
  const char* home_dir = getenv("HOME");
  if (home_dir == NULL) {
    fprintf(stderr, "Cannot find HOME dir!\n");
    return NULL;
  }

  char* cache_path = NULL;
  catpath(&cache_path, home_dir);
  catpath(&cache_path, ".cache/gpack.cache/packages/tarballs");

  // Create the directory
  // TODO: use C calls
  char mkdir_cmd[200];
  mkdir_cmd[0] = '\0';
  sprintf(mkdir_cmd, "mkdir -p %s", cache_path);
  if (system(mkdir_cmd) != 0) {
    print_errorf("mkdir command failed\n");
    free(cache_path);
    return NULL;
  }

  catpath(&cache_path, sha);

  // Create a new pointer with the currect len (8 for ".tar.gz", and 2 for extra)
  char* full_path = (char*) malloc(strlen(cache_path) + 8 + 2);

  strcpy(full_path, cache_path);
  strcat(full_path, ".tar.gz");

  free(cache_path);

  return full_path;
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
    print_warningf("Checksum missmatch: expecting: %08x (%s) got: %08x\n", file_checksum, checksum, verify_checksum);
    print_warningf("Invalid checksum, cannot ensure data...\n");
  }

  fclose(fp_check);

  return 0;
}

// vim: tabstop=2 shiftwidth=2 expandtab autoindent softtabstop=0

