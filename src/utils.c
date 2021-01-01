// Created by: WestleyR
// Email: westleyr@nym.hush.com
// Url: https://github.com/WestleyR/gpack
// Last modified date: 2020-12-31
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

// New functions!!! TODO:

const char* get_installdir_for_user_and_version(const char* user_name, const char* name, const char* version) {
  char* path;
  path = (char*) malloc(256);

  char* h = getenv("HOME");
  if (h == NULL) {
    fprintf(stderr, "Cant find home directory\n");
    return(NULL);
  }

  path = path_join(h, ".gpack/installed");
  path = path_join(path, user_name);
  path = path_join(path, name);
  path = path_join(path, version);

  // TODO: use C functions
  char mkdir_cmd[200];
  mkdir_cmd[0] = '\0';

  sprintf(mkdir_cmd, "mkdir -p %s", path);
  if (system(mkdir_cmd) != 0) {
    print_errorf("Failed to run mkdir command\n");
    free(path);
    return NULL;
  }

  return(path);
}

// End new functions!!!


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

//*****************
// Unused functions
//*****************

void append(char* s, char c) {
  int len = strlen(s);
  s[len] = c;
  s[len+1] = '\0';
}


// delimiters:
// 0 = binary name
// 1 = installed path
// 2 = checksum
char** get_installed_files_from_map(const char* map, int delimiter) {
  int installed_files_index = 0;
  // TODO: should handle more then 5 lines, ie. installed files
  char** installed_files = (char**) malloc(5);
  // TODO: error check

  for (int i = 0; i < 5; i++) {
    installed_files[i] = (char*) malloc(50);
    // TODO: error check
  }

  FILE* fp = fopen(map, "r");
  if (fp == NULL) {
    //    printf("ERROR: failed to open file\n");
    //    perror("fopen");
    return NULL;
  }

  installed_files[0][0] = '\0';

  char item[256];
  item[0] = '\0';

  int del = 0;
  char c;
  while ((c = fgetc(fp)) != EOF) {
    if (c == ' ') {
      del++;
    }

    if (c == '\n') {
      installed_files[installed_files_index][0] = '\0';
      strcpy(installed_files[installed_files_index], item);
      installed_files_index++;
      del = 0;
      //printf("ITEM: %s\n", item);
      item[0] = '\0';
      continue;
    }

    if (c == ' ') {
      continue;
    }

    if (del == delimiter) {
      append(item, c);
    }
  }
  fclose(fp);

  return installed_files;
}

// vim: tabstop=2 shiftwidth=2 expandtab autoindent softtabstop=0
