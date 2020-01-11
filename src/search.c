// Created by: WestleyR
// email: westleyr@nym.hush.com
// Date: Jan 9, 2020
// https://github.com/WestleyR/gpack
// version-1.0.0
//
// The Clear BSD License
//
// Copyright (c) 2019 WestleyR
// All rights reserved.
//
// This software is licensed under a Clear BSD License.
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
