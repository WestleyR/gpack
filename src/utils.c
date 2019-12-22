// Created by: WestleyR
// email: westleyr@nym.hush.com
// Date: Dec 21, 2019
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

char* get_installed_pkg_version(const char* usr_pkg, const char* pkg) {
  char* version_file = path_join(usr_pkg, pkg);
  version_file = path_join(version_file, "version.gpack");

  print_debugf("Full version file path: %s\n", version_file);

  char line[128];

  FILE* fp = fopen(version_file, "r");
  if (fp == NULL) {
    print_debugf("Failed to open: %s\n", version_file);
    return(NULL);
  }

  char* ret;
  ret = (char*) malloc(32 * sizeof(char));
  if (ret == NULL) {
    print_debugf("malloc failed\n");
    return (NULL);
  }

  while(fgets(line, sizeof(line), fp) != NULL) {
    if (line != NULL) {
      if (line[strlen(line)-1] == '\n') line[strlen(line)-1] = '\0';
      strcpy(ret, line);
    }
  }

  fclose(fp);
  free(version_file);

  return(ret);
}

char* get_installer() {
  char* h = getenv("HOME");
  if (h == NULL) {
    fprintf(stderr, "Cant find home directory\n");
    return(NULL);
  }

  char* ret = path_join(h, ".gpack/gpack/cmd/gpack-installer ");

  return(ret);
}

char* get_update_script() {
  char* h = getenv("HOME");
  if (h == NULL) {
    fprintf(stderr, "Cant find home directory\n");
    return(NULL);
  }

  char* ret = path_join(h, ".gpack/gpack/cmd/gpack-update");

  return(ret);
}

char* get_upgrade_script() {
  char* h = getenv("HOME");
  if (h == NULL) {
    fprintf(stderr, "Cant find home directory\n");
    return(NULL);
  }

  char* ret = path_join(h, ".gpack/gpack/cmd/gpack-upgrade");

  return(ret);
}

char* get_bin() {
  char* h = getenv("HOME");
  if (h == NULL) {
    fprintf(stderr, "Cant find home directory\n");
    return(NULL);
  }

  char* ret = path_join(h, ".gpack/bin");

  return(ret);
}

char* get_lib_dir() {
  char* h = getenv("HOME");
  if (h == NULL) {
    fprintf(stderr, "Cant find home directory\n");
    return(NULL);
  }

  char* ret = path_join(h, "/.local/lib");

  return(ret);
}

char* get_include_dir() {
  char* h = getenv("HOME");
  if (h == NULL) {
    fprintf(stderr, "Cant find home directory\n");
    return(NULL);
  }

  char* ret = path_join(h, "/.local/include");

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
