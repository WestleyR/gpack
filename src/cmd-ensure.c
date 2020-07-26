// Created by: WestleyR
// Email: westleyr@nym.hush.com
// Url: https://github.com/WestleyR/gpack
// Last modified date: 2020-07-25
//
// This file is licensed under the terms of
//
// The Clear BSD License
//
// Copyright (c) 2020 WestleyR
// All rights reserved.
//
// This software is licensed under a Clear BSD License.
//

//
// Contributors:
//
// WestleyR <westleyr@nym.hush.com>
//

#include "cmd-ensure.h"

int ensure_all_scripts() {
  char* checkfile = get_cmd_checksum_file();
  FILE* fp = fopen(checkfile, "r");
  if (fp == NULL) {
    print_errorf("Failed to open file\n");
    // Return 0 incase the file does not exists
    return 0;
  }

  return check_crc32_file(fp, SSUM_BLOCK_SIZE);
}

// vim: tabstop=2 shiftwidth=2 expandtab autoindent softtabstop=0

