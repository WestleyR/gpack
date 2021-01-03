// Created by: WestleyR
// Email: westleyr@nym.hush.com
// Url: https://github.com/WestleyR/gpack
// Last modified date: 2021-01-02
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

int remove_pkg(char *pkg) {
  print_debugf("Removing: %s\n", pkg);

  char cmd[256];
  cmd[0] = '\0';

  char pkg_file[200];
  pkg_file[0] = '\0';

  strcpy(pkg_file, "installed/");
  strcat(pkg_file, pkg);

  strcpy(cmd, "rm -rf ${HOME}/.gpack/installed/");
  strcat(cmd, pkg);

  char installed_pkg[256];
  installed_pkg[0] = '\0';

  char* h = getenv("HOME");

  strcpy(installed_pkg, h);
  strcat(installed_pkg, "/.gpack/installed/");
  strcat(installed_pkg, pkg);

  struct stat sb;
  if (stat(installed_pkg, &sb) != 0 || !S_ISDIR(sb.st_mode)) {
    printf("%s: is not installed\n", pkg);
    return 1;
  }

  char* ispk = strtok(pkg, "/");
  int sc = 0;
  while (ispk != NULL) {
    ispk = strtok(NULL, "/");
    sc++;
  }
  if (sc == 1) {
    fprintf(stderr, "No Package to remove\n");
    fprintf(stderr, "This will remove the user: %s and all you installed from that user\n", pkg);
    fprintf(stderr, "Enter the username to continue: ");
    char cont[strlen(pkg) + 2];
    scanf(" %[^\n]", cont);
    if (strcmp(cont, pkg) != 0) {
      fprintf(stderr, "Aborting\n");
      return(1);
    }
  }

  print_debugf("About to run: %s\n", cmd);

  system("sleep 1s");
  system(cmd);

  print_debugf("Autocleaning...\n");
  int err = helper_autoclean(0);
  if (err != 0) {
    print_errorf("Failed to run autoclean(): exit status: %d\n", err);
    return err;
  }

  return(0);
}

// vim: tabstop=2 shiftwidth=2 expandtab autoindent softtabstop=0
