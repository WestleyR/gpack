// Created by: WestleyR
// email: westleyr@nym.hush.com
// Date: Dec 18, 2019
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

char* get_installer() {
  char* ret;
  ret = (char*) malloc(100);

  char* h = getenv("HOME");
  if (h == NULL) {
    fprintf(stderr, "Cant find home directory\n");
    return(NULL);
  }

  strcpy(ret, h);
  strcat(ret, "/.gpack/gpack/cmd/gpack-installer ");

  return(ret);
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

  return(ret);
}

char* get_lib_dir() {
  char* h = getenv("HOME");
  if (h == NULL) {
    fprintf(stderr, "Cant find home directory\n");
    return(NULL);
  }

  char* ret;
  // strlen(h) for HOME, and 12 for '/.local/lib', 2 for extra
  ret = (char*) malloc(sizeof(char) * (strlen(h) + 12 + 2));
  if (ret == NULL) {
    fprintf(stderr, "Malloc failed\n");
    return(NULL);
  }

  strcpy(ret, h);
  strcat(ret, "/.local/lib");

  return(ret);
}

char* get_include_dir() {
  char* h = getenv("HOME");
  if (h == NULL) {
    fprintf(stderr, "Cant find home directory\n");
    return(NULL);
  }

  char* ret;
  ret = (char*) malloc(sizeof(char) * (strlen(h) + 16 + 2));
  if (ret == NULL) {
    fprintf(stderr, "Malloc failed\n");
    return(NULL);
  }

  strcpy(ret, h);
  strcat(ret, "/.local/include");

  return(ret);
}

char* get_package_dir() {
  char* path;

  path = (char*) malloc(100);

  char* h = getenv("HOME");
  if (h == NULL) {
    fprintf(stderr, "Cant find home directory\n");
    return(NULL);
  }

  strcpy(path, h);
  strcat(path, "/.gpack/gpack/packages/");

  return(path);
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

  return(path);
}

// vim: tabstop=2 shiftwidth=2 expandtab autoindent softtabstop=0
