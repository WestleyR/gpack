// Created by: WestleyR
// Email(s): westleyr@nym.hush.com
// Last modifyed date: Jan 31, 2020
// This file version-1.0.0
//
// This file is part of the gpack software:
// https://github.com/WestleyR/gpack
//
// Which that software and this file is licensed under:
//
// The Clear BSD License
//
// Copyright (c) 2019-2020 WestleyR
// All rights reserved.
//
// This software is licensed under a Clear BSD License.
//

#include "list.h"

int print_package(const char* path, const char* name) {
  DIR *dir;
  struct dirent *d;
  dir = opendir(path);
  if (dir == NULL) {
    fprintf(stderr, "Failed to open: %s\n", path);
    return(1);
  }

  while ((d = readdir(dir)) != NULL) {
    if (*d->d_name != '.' && strcmp(d->d_name, "..") != 0) {
      char *pkg_version = get_installed_pkg_version(path, d->d_name);
      printf("%s/%s", name, d->d_name);
      for (int i = strlen(name) + strlen(d->d_name) + 1; i < 38; i++) printf(" ");
      printf(" %s\n", pkg_version);
      free(pkg_version);
    }
  }
  closedir(dir);

  return(0);
}

int list_packages() {
  char* ppath = get_package_prefix();

  DIR *dir;
  struct dirent *d;
  dir = opendir(ppath);
  if (dir == NULL) {
    fprintf(stderr, "Failed to open: %s\n", ppath);
    return(1);
  }

  char pkg[256];
  pkg[0] = '\0';

  char full_path[256];
  full_path[0] = '\0';

  while ((d = readdir(dir)) != NULL) {
    if (*d->d_name != '.' && strcmp(d->d_name, "..") != 0) {
      strcpy(pkg, d->d_name);
      strcpy(full_path, ppath);
      strcat(full_path, d->d_name);
      print_package(full_path, pkg);
    }
  }
  closedir(dir);

  free(ppath);

  return 0;
}

// vim: tabstop=2 shiftwidth=2 expandtab autoindent softtabstop=0
