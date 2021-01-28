// Created by: WestleyR
// Email: westleyr@nym.hush.com
// Url: https://github.com/WestleyR/gpack
// Last modified date: 2021-01-06
//
// This file is licensed under the terms of
//
// The Clear BSD License
//
// Copyright (c) 2019-2021 WestleyR
// All rights reserved.
//
// This software is licensed under a Clear BSD License.
//

#include "remove-pkg.h"

int remove_pkg(const char *pkg) {
  print_debugf("Removing: %s\n", pkg);

  char* h = getenv("HOME");

  char* installed_pkg = NULL;
  catpath(&installed_pkg, h);
  catpath(&installed_pkg, ".gpack/installed");
  catpath(&installed_pkg, pkg);

  struct stat sb;
  if (stat(installed_pkg, &sb) != 0 || !S_ISDIR(sb.st_mode)) {
    free(installed_pkg);
    printf("%s: is not installed\n", pkg);
    return 1;
  }

  free(installed_pkg);

  char* pkg_dup = strdup(pkg);
  char* ispk = strtok(pkg_dup, "/");
  int sc = 0;
  while (ispk != NULL) {
    ispk = strtok(NULL, "/");
    sc++;
  }
  free(pkg_dup);
  if (sc == 1) {
    fprintf(stderr, "No Package to remove\n");
    fprintf(stderr, "This will remove the user: %s and all you installed from that user\n", pkg);
    fprintf(stderr, "Enter the username to continue: ");
    char cont[strlen(pkg) + 2];
    scanf(" %[^\n]", cont);
    if (strcmp(cont, pkg) != 0) {
      fprintf(stderr, "Aborting\n");
      return 1;
    }
  }

  char cmd[256];
  cmd[0] = '\0';
  strcpy(cmd, "rm -rf ${HOME}/.gpack/installed/");
  strcat(cmd, pkg);

  print_debugf("About to run: %s\n", cmd);
  sleep(1);

  if (system(cmd) != 0) {
    print_errorf("Failed to run: %s\n", cmd);
    return -1;
  }

  // New remove the broken link
  print_debugf("Autocleaning...\n");
  int err = helper_autoclean(0);
  if (err != 0) {
    print_errorf("Failed to run autoclean(): exit status: %d\n", err);
    return err;
  }

  return 0;
}

// vim: tabstop=2 shiftwidth=2 expandtab autoindent softtabstop=0
