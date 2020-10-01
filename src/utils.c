// Created by: WestleyR
// Email: westleyr@nym.hush.com
// Url: https://github.com/WestleyR/gpack
// Last modified date: 2020-09-30
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

#include "utils.h"


char* get_listmap_for_pkg(const char* user_name, const char* pkg) {
  char* h = getenv("HOME");
  if (h == NULL) {
    fprintf(stderr, "Cant find home directory\n");
    return(NULL);
  }

  char* ret = path_join(h, ".gpack/installed");
  ret = path_join(ret, user_name);
  ret = path_join(ret, pkg);
  ret = path_join(ret, "list.gpack");

  return(ret);
}

char* get_cmd_checksum_file() {
  char* h = getenv("HOME");
  if (h == NULL) {
    fprintf(stderr, "Cant find home directory\n");
    return(NULL);
  }

  char* ret = path_join(h, ".gpack/gpack/cmd-checksum.ssum");

  return(ret);
}

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
  ret = (char*) malloc(64 * sizeof(char));
  if (ret == NULL) {
    print_debugf("malloc failed\n");
    return(NULL);
  }

  while(fgets(line, sizeof(line), fp) != NULL) {
    if (line[0] != '\0') {
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

char* get_search_script() {
  char* h = getenv("HOME");
  if (h == NULL) {
    fprintf(stderr, "Cant find home directory\n");
    return(NULL);
  }

  char* ret = path_join(h, ".gpack/gpack/cmd/gpack-search");

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

  char* ret = path_join(h, ".local/bin");

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
  strcat(path, "/.gpack/packages/");

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
