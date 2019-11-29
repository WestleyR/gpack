// Created by: WestleyR
// email: westleyr@nym.hush.com
// Date: Jun 16, 2019
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

#include "install-pkg.h"

char* replace_char(char* str, char find, char replace){
  char *current_pos = strchr(str,find);
  while (current_pos) {
    *current_pos = replace;
    current_pos = strchr(current_pos,find);
  }
  return str;
}

int open_package(const char* pkg) {
  char pkg_file[256];
  pkg_file[0] = '\0';


  char* h = getenv("HOME");
  if (h == NULL) {
    printf("HOME not set!???\n");
    return(1);
  }

  strcpy(pkg_file, h);
  strcat(pkg_file, "/.gpack/gpack/packages/");
  strcat(pkg_file, pkg);

  FILE* fp = fopen(pkg_file, "r");
  if (fp == NULL) {
    fprintf(stderr, "%s: package does not exist\n", pkg);
    return -1;
  }
  fclose(fp);


  char installed_pkg[256];
  installed_pkg[0] = '\0';

  strcpy(installed_pkg, h);
  strcat(installed_pkg, "/.gpack/installed/");
  strcat(installed_pkg, pkg);

  struct stat sb;
  if (stat(installed_pkg, &sb) == 0 && S_ISDIR(sb.st_mode)) {
    printf("%s: is already installed\n", pkg);
    return 1;
  }

  printf("Executing install script...\n");

  char cmd[strlen(pkg_file) + 5];
  cmd[0] = '\0';

  strcpy(cmd, "sh ");
  strcat(cmd, pkg_file);

  if (system(cmd) != 0) {
    fprintf(stderr, "Failed to install: %s\n", pkg);
    fprintf(stderr, "Cleaning up...\n");
    remove_pkg(pkg);
    return(1);
  }

  return 0;
}

int install_pkg(const char* pkg) {

  int ret = open_package(pkg);

  return ret;
}

// vim: tabstop=2 shiftwidth=2 expandtab autoindent softtabstop=0
