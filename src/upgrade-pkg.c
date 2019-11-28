// Created by: WestleyR
// email: westleyr@nym.hush.com
// Date: Nov 28, 2019
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

int upgrade_pkg() {
  printf("I: Upgrading...\n");
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
      DIR *newdir;
      struct dirent *de;
      newdir = opendir(full_path);
      if (newdir == NULL) {
        fprintf(stderr, "Failed to open: %s\n", full_path);
        return(1);
      }

      while ((de = readdir(newdir)) != NULL) {
        if (*de->d_name != '.' && strcmp(de->d_name, "..") != 0) {
          char version_file[128];
          version_file[0] = '\0';

          strcpy(version_file, ppath);
          strcat(version_file, d->d_name);
          strcat(version_file, "/");
          strcat(version_file, de->d_name);
          strcat(version_file, "/version.gpack");
          printf("Version file: %s\n", version_file);
          if (access(version_file, F_OK) == 0) {
            printf("OK: %s\n", version_file);
          } else {
            printf("WARNING: No version file found for: %s\n", version_file);
          }
        }
      }
      closedir(newdir);
    }
  }
  closedir(dir);

  free(ppath);

  printf("I: Done\n");

  return(0);
}


// vim: tabstop=2 shiftwidth=2 expandtab autoindent softtabstop=0
