//
//  search.c
//  gpack - https://github.com/WestleyR/gpack
//
// Created by WestleyR on Dec 25, 2019
// Source code: https://github.com/WestleyR/gpack
//
// Copyright (c) 2019-2021 WestleyR. All rights reserved.
// This software is licensed under a BSD 3-Clause Clear License.
// Consult the LICENSE file that came with this software regarding
// your rights to distribute this software.
//

#include "search.h"

int search_pkg(const char* pat, int print) {
  char* search_script = get_search_script();
  if (search_script == NULL) {
    print_debugf("Failed to get search script\n");
    return(1);
  }

  char cmd[256];

  print_debugf("Search script: %s\n", search_script);

  strcpy(cmd, search_script);

  if (pat[0] != '\0') {
    strcat(cmd, " ");
    strcat(cmd, pat);
  }

  print_debugf("Running command: %s\n", cmd);

  if (system(cmd) != 0) {
    fprintf(stderr, "Failed to run search script\n");
    free(search_script);
    return(1);
  }

  free(search_script);

  return(0);
}

// vim: tabstop=2 shiftwidth=2 expandtab autoindent softtabstop=0
