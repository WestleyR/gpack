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

#include "utils.h"


char* get_pkg_version(const char* pkg) {


  return(NULL);
}

char* get_update_script() {
  char* ret;
  ret = (char*) malloc(100);

  char* h = getenv("HOME");
  if (h == NULL) {
    fprintf(stderr, "Cant find home directory\n");
    return(NULL);
  }

  strcpy(ret, h);
  strcat(ret, "/.gpack/gpack/cmd/gpack-update");

  return(ret);
}

char* get_bin() {
  char* ret;
  ret = (char*) malloc(100);

  char* h = getenv("HOME");
  if (h == NULL) {
    fprintf(stderr, "Cant find home directory\n");
    return(NULL);
  }

  strcpy(ret, h);
  strcat(ret, "/.gpack/bin");

  // TODO: free(h)?

  return(ret);
}

char* get_package_prefix() {
  char* path;

  path = (char*) malloc(100);

  char* h = getenv("HOME");
  if (h == NULL) {
    fprintf(stderr, "Cant find home directory\n");
    return(NULL);
  }

  strcpy(path, h);
  strcat(path, "/.gpack/installed/");

  // TODO: free(h)?

  return(path);
}

// vim: tabstop=2 shiftwidth=2 expandtab autoindent softtabstop=0
