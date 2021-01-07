// Created by: WestleyR
// Email: westleyr@nym.hush.com
// Url: https://github.com/WestleyR/gpack
// Last modified date: 2021-01-06
//
// This file is licensed under the terms of
//
// The Clear BSD License
//
// Copyright (c) 2020-2021 WestleyR
// All rights reserved.
//
// This software is licensed under a Clear BSD License.
//

#include "check-pkgs.h"

int count_files(const char *name) {
  DIR *dir;
  struct dirent *filef;
  int ret = 0;

  if (!(dir = opendir(name))) return -1;

  while ((filef = readdir(dir)) != NULL) {
    if (filef->d_type == DT_DIR) {
      char path[1024];
      if (*filef->d_name == '.' || strcmp(filef->d_name, "..") == 0) continue;

      snprintf(path, sizeof(path), "%s/%s", name, filef->d_name);
      ret += count_files(path);
    } else {
      ret++;
    }
  }
  closedir(dir);

  return ret;
}

int check_installed_pkg() {
  int count = 0;

  char* ppath = package_install_dir();
  count = count_files(ppath);
  free(ppath);

  return count;
}

// vim: tabstop=2 shiftwidth=2 expandtab autoindent softtabstop=0
