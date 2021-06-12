//
//  repo-parser.c for gpack
//  https://github.com/WestleyR/gpack
//
// Created by WestleyR on 2021-06-10
// Source code: https://github.com/WestleyR/gpack
//
// Copyright (c) 2021 WestleyR. All rights reserved.
// This software is licensed under a BSD 3-Clause Clear License.
// Consult the LICENSE file that came with this software regarding
// your rights to distribute this software.
//

#include "helper.h"

char* cpstr(const char* str) {
  char* ret = (char*) malloc(strlen(str) + 2);
  if (ret == NULL) {
    fprintf(stderr, "%s:%s():%d: Failed to malloc: ", __FILE__, __func__, __LINE__);
    perror("malloc");
    exit(255);
  }

  strcpy(ret, str);

  return ret;
}

// vim: tabstop=2 shiftwidth=2 expandtab autoindent softtabstop=0
