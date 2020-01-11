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

#include "upgrade-pkg.h"

int upgrade_pkg(int compile_build) {
  printf("I: Checking out-of-date packages...\n");

  char* upgrade_script = get_upgrade_script();
  if (upgrade_script == NULL) {
    fprintf(stderr, "Failed to get upgrade script\n");
    return(-1);
  }

  char* upgrade_command;
  upgrade_command = (char*) malloc((strlen(upgrade_script) + 26 + 2) * sizeof(char));
  if (upgrade_command == NULL) {
    print_debugf("FAIL: malloc failed with buffer size of: %d\n", (long)(strlen(upgrade_script) + 26 + 2) * sizeof(char));
    return(-1);
  }

  if (compile_build == 1) {
    strcpy(upgrade_command, "GPACK_COMPILE_BUILD=true ");
    strcat(upgrade_command, upgrade_script);
  } else {
    strcpy(upgrade_command, upgrade_script);
  }

  if (system(upgrade_command) != 0) {
    fprintf(stderr, "Failed to run upgrade script\n");
    free(upgrade_script);
    free(upgrade_command);
    return(-1);
  }

  free(upgrade_script);
  free(upgrade_command);

  return(0);
}

// vim: tabstop=2 shiftwidth=2 expandtab autoindent softtabstop=0
