// Created by: WestleyR
// email: westleyr@nym.hush.com
// Date: Nov 28, 2019
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

#include "update-pkg.h"

int update_pkg() {
  printf("I: Updateing...\n");

  char* update_script = get_update_script();
  if (update_script == NULL) {
    fprintf(stderr, "Failed to get update script\n");
    return(1);
  }

  printf("Update script: %s\n", update_script);

  // TODO: add shasum verify to update script
  
  if (system(update_script) != 0) {
    fprintf(stderr, "Failed to run update script\n");
    free(update_script);
    return(1);
  }

  free(update_script);

  printf("I: Done\n");

  return(0);
}

// vim: tabstop=2 shiftwidth=2 expandtab autoindent softtabstop=0
