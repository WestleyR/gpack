// Created by: WestleyR
// Email: westleyr@nym.hush.com
// Url: https://github.com/WestleyR/gpack
// Last modified date: 2020-04-21
//
// This file is licensed under the terms of
//
// The Clear BSD License
//
// Copyright (c) 2019-2020 WestleyR
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

int open_package(const char* pkg, int overide, int compile_build) {
  char pkg_file[256];
  pkg_file[0] = '\0';

  char* h = getenv("HOME");
  if (h == NULL) {
    printf("HOME not set!???\n");
    return(1);
  }

  strcpy(pkg_file, h);
  strcat(pkg_file, "/.gpack/packages/");
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

  if (overide == 0) {
    struct stat sb;
    if (stat(installed_pkg, &sb) == 0 && S_ISDIR(sb.st_mode)) {
      printf("%s: is already installed\n", pkg);
      // TODO: this should not be 0
      return(0);
    }
  }

  char cmd[256];
  cmd[0] = '\0';

  char* installer_script = get_installer();

  if (compile_build == 1) {
    printf("I: Compiling from release\n");
    strcpy(cmd, "GPACK_COMPILE_BUILD=true ");
  }
  if (overide == 1) {
    print_debugf("Overidding install...\n");
    strcpy(cmd, "GPACK_OVERIDE=true ");
  }
  // TODO: when the logger package supports this function
  //if (debug_status() == 1) {
  //  strcpy(cmd, "GPACK_DEBUG=true ");
  //}
  strcat(cmd, installer_script);

  free(installer_script);

  strcat(cmd, pkg_file);

#ifdef DEBUG
  printf("Executing install script: %s\n", cmd);
#endif

  if (system(cmd) != 0) {
    fprintf(stderr, "Failed to install: %s\n", pkg);
    print_debugf("Removing package that failed to install...\n");
    remove_pkg(pkg);
    return(1);
  }

  return 0;
}

int install_pkg(const char* pkg, int check_installed, int compile_build, int overide) {
  if (open_package(pkg, overide, compile_build) != 0) {
    return(1);
  }

  printf("I: Done installing %s\n", pkg);

  return(0);
}

// vim: tabstop=2 shiftwidth=2 expandtab autoindent softtabstop=0
