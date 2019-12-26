// Created by: WestleyR
// email: westleyr@nym.hush.com
// Date: Dec 25, 2019
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

#include "search.h"

int get_pkg(const char* path, const char* pat) {
  DIR *dir;
  struct dirent *d;
  dir = opendir(path);
  if (dir == NULL) {
    fprintf(stderr, "Failed to open: %s\n", path);
    return(1);
  }

  char full_file_path[256];
  full_file_path[0] = '\0';

  while ((d = readdir(dir)) != NULL) {
    if (*d->d_name != '.' && strcmp(d->d_name, "..") != 0) {
      strcpy(full_file_path, path);
      strcat(full_file_path, "/");
      strcat(full_file_path, d->d_name);

      char* search_script = get_search_script();
      if (search_script == NULL) {
        print_debugf("Failed to get search script\n");
        return(1);
      }

      char cmd[256];

      strcpy(cmd, search_script);
      strcat(cmd, " ");
      strcat(cmd, full_file_path);
      strcat(cmd, " ");
      strcat(cmd, pat);

      if (system(cmd) != 0) {
        fprintf(stderr, "Failed to run search script\n");
        return(1);
      }
    }
  }

  closedir(dir);

  return(0);
}

int search_pkg(const char* pat, int print) {
  char* pkg_dir = get_package_dir();
  if (pkg_dir == NULL) {
    print_debugf("Failed to get pkg_dir\n");
    return(-1);
  }

  DIR *dir;
  struct dirent *d;
  dir = opendir(pkg_dir);
  if (dir == NULL) {
    fprintf(stderr, "Failed to open: %s\n", pkg_dir);
    return(1);
  }

  struct stat info;
  char full_file_path[256];
  full_file_path[0] = '\0';

  while ((d = readdir(dir)) != NULL) {
    if (*d->d_name != '.' && strcmp(d->d_name, "..") != 0) {
      strcpy(full_file_path, pkg_dir);
      strcat(full_file_path, "/");
      strcat(full_file_path, d->d_name);

      if (stat(full_file_path, &info) != 0) {
        fprintf(stderr, "Failed to open: %s\n", full_file_path);
        return(-1);
      }
      if (!S_ISREG(info.st_mode)) {
        get_pkg(full_file_path, pat);
      }

      //printf("FULL_FILE_PATH: %s\n", full_file_path);

    }
  }

  closedir(dir);

  return(0);
}

// vim: tabstop=2 shiftwidth=2 expandtab autoindent softtabstop=0
