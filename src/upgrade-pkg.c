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

char* get_static_version(const char* pkg) {
  char path[256];

  char* ppath = get_package_dir();

  strcpy(path, ppath);
  strcat(path, pkg);

  FILE* fp = fopen(path, "r");
  if (fp == NULL) {
    printf("Failed to open: %s\n", path);
    return(NULL);
  }

  char* ret;
  ret = (char*) malloc(100);

  char line[200];

  while (fgets(line, sizeof(line), fp)) {
    if (strstr(line, "PKG_VERSION")) {
      char* v = strtok(line, "\n");
      strcpy(ret, v);
      break;
    }
  }

  free(ppath);

  return(ret);
}

char* read_file(const char* path) {
  FILE* fp = fopen(path, "r");
  if (fp == NULL) {
    printf("Failed to open: %s\n", path);
    return(NULL);
  }

  char* ret;
  ret = (char*) malloc(100);

  char line[200];

  while (fgets(line, sizeof(line), fp)) {
    if (line[0] != '\0') {
      if (line[strlen(line)-1] == '\n') {
        line[strlen(line)-1] = '\0';
        strcpy(ret, line);
      } else {
        strcpy(ret, line);
      }
      break;
    }
  }

  return(ret);
}

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
          char version_file[256];
          version_file[0] = '\0';

          strcpy(version_file, d->d_name);
          strcat(version_file, "/");
          strcat(version_file, de->d_name);

          char* pkg_name = strdup(version_file);
          char* static_version = get_static_version(version_file);

          version_file[0] = '\0';

          strcpy(version_file, ppath);
          strcat(version_file, d->d_name);
          strcat(version_file, "/");
          strcat(version_file, de->d_name);
          strcat(version_file, "/version.gpack");
          if (access(version_file, F_OK) == 0) {
            printf("OK: %s\n", version_file);
            char* current_version = read_file(version_file);
            if (current_version == NULL) {
              printf("Error\n");
              return(1);
            }

#ifdef DEBUG
            printf("Current version: %s; for: %s\n", current_version, version_file);
            printf("Static version: %s\n", static_version);
#endif

            if (strstr(static_version, current_version)) {
              if (strcmp(current_version, "master") == 0) {
                if (reinstall_pkg(pkg_name) != 0) {
                  printf("Failed to reinstall pkg\n");
                }
              } else {
                printf("%s: Already up to date\n", pkg_name);
              }
            } else {
              printf("Reinstalling: %s\n", pkg_name);
              if (reinstall_pkg(pkg_name) != 0) {
                printf("Failed to reinstall pkg\n");
              }
            }

            free(current_version);
          } else {
            printf("WARNING: No version file found for: %s\n", pkg_name);
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
