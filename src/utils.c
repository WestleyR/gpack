//
//  utils.c
//  gpack - https://github.com/WestleyR/gpack
//
// Created by WestleyR on Nov 28, 2019
// Source code: https://github.com/WestleyR/gpack
//
// Copyright (c) 2019-2021 WestleyR. All rights reserved.
// This software is licensed under a BSD 3-Clause Clear License.
// Consult the LICENSE file that came with this software regarding
// your rights to distribute this software.
//

#include "utils.h"

// New functions!!! TODO:

char* get_installdir_for_user_and_version(const char* user_name, const char* name, const char* version) {
  char* path =  NULL;

  char* h = getenv("HOME");
  if (h == NULL) {
    fprintf(stderr, "Cant find home directory\n");
    return(NULL);
  }

  catpath(&path, h);
  catpath(&path, ".gpack/installed");
  catpath(&path, user_name);
  catpath(&path, name);
  catpath(&path, version);

  // TODO: use C functions
  char mkdir_cmd[200];
  mkdir_cmd[0] = '\0';

  sprintf(mkdir_cmd, "mkdir -p %s", path);
  if (system(mkdir_cmd) != 0) {
    print_errorf("Failed to run mkdir command\n");
    return NULL;
  }

  return(path);
}

// Return needs to be free()
char* pkg_file_registry_dir() {
  char* h = getenv("HOME");
  if (h == NULL) {
    fprintf(stderr, "Cant find home directory\n");
    return(NULL);
  }
  char* path = NULL;
  catpath(&path, h);
  catpath(&path, ".gpack/packages/packages");

  return(path);
}

// Return pointer must be freed.
char* package_install_dir() {
  char* h = getenv("HOME");
  if (h == NULL) {
    fprintf(stderr, "Cant find home directory\n");
    return NULL;
  }

  char* path = NULL;
  catpath(&path, h);
  catpath(&path, ".gpack/installed");

  return path;
}

// Takes values like WestleyR, and srm as the arguments.
// Return value must be freed.
char* get_installed_pkg_version(const char* usr_pkg, const char* pkg) {
  // Build the version file path
  char* version_file = package_install_dir();
  catpath(&version_file, usr_pkg);
  catpath(&version_file, pkg);
  catpath(&version_file, "version.gpack");

  print_debugf("Full version file path: %s\n", version_file);

  // Open the version file
  FILE* fp = fopen(version_file, "r");
  if (fp == NULL) {
    print_debugf("Failed to open: %s\n", version_file);
    free(version_file);
    return NULL;
  }

  free(version_file);

  char* ret;
  ret = (char*) malloc(64 * sizeof(char));
  if (ret == NULL) {
    print_debugf("malloc failed\n");
    return NULL;
  }

  char line[128];
  while(fgets(line, sizeof(line), fp) != NULL) {
    if (line[0] != '\0') {
      if (line[strlen(line)-1] == '\n') line[strlen(line)-1] = '\0';
      strcpy(ret, line);
    }
  }

  fclose(fp);

  return ret;
}

// Takes values like: WestleyR, srm. Returned value must be freed.
char* get_latest_version_for_pkg(const char* user_name, const char* pkg) {
  char* ini_file = pkg_file_registry_dir();

  catpath(&ini_file, user_name);
  catpath(&ini_file, pkg);

  FILE* fp = fopen(ini_file, "r");
  if (fp == NULL) {
    fprintf(stderr, "Failed to open: %s\n", pkg);
    free(ini_file);
    return NULL;
  }

  // Load the package file into memory
  fseek(fp, 0, SEEK_END);
  int size = ftell(fp);
  fseek(fp, 0, SEEK_SET);
  char* data = (char*) malloc(size + 1);
  fread(data, 1, size, fp);
  data[size] = '\0';
  fclose(fp);

  ini_t* ini = ini_load(data, NULL);
  free(data);

  const char* latest_pkg_version = get_package_version(ini);

  char* latest_pkg_version_dup = strdup(latest_pkg_version);

  ini_destroy(ini);
  free(ini_file);

  return latest_pkg_version_dup;
}

// End new functions!!!

char* get_cmd_checksum_file() {
  char* h = getenv("HOME");
  if (h == NULL) {
    fprintf(stderr, "Cant find home directory\n");
    return NULL;
  }

  char* ret = NULL;
  catpath(&ret, h);
  catpath(&ret, ".gpack/gpack/cmd-checksum.ssum");

  return ret;
}

char* get_update_script() {
  char* h = getenv("HOME");
  if (h == NULL) {
    fprintf(stderr, "Cant find home directory\n");
    return NULL;
  }

  char* ret = NULL;
  catpath(&ret, h);
  catpath(&ret, ".gpack/gpack/cmd/gpack-update");

  return ret;
}

char* get_search_script() {
  char* h = getenv("HOME");
  if (h == NULL) {
    fprintf(stderr, "Cant find home directory\n");
    return NULL;
  }

  char* ret = NULL;
  catpath(&ret, h);
  catpath(&ret, ".gpack/gpack/cmd/gpack-search");

  return ret;
}

char* get_upgrade_script() {
  char* h = getenv("HOME");
  if (h == NULL) {
    fprintf(stderr, "Cant find home directory\n");
    return NULL;
  }

  char* ret = NULL;
  catpath(&ret, h);
  catpath(&ret, ".gpack/gpack/cmd/gpack-upgrade");

  return ret;
}

char* get_bin() {
  char* h = getenv("HOME");
  if (h == NULL) {
    fprintf(stderr, "Cant find home directory\n");
    return NULL;
  }

  char* ret = NULL;
  catpath(&ret, h);
  catpath(&ret, ".local/bin");

  return ret;
}

char* get_lib_dir() {
  char* h = getenv("HOME");
  if (h == NULL) {
    fprintf(stderr, "Cant find home directory\n");
    return NULL;
  }

  char* ret = NULL;
  catpath(&ret, h);
  catpath(&ret, ".local/lib");

  return ret;
}

char* get_include_dir() {
  char* h = getenv("HOME");
  if (h == NULL) {
    fprintf(stderr, "Cant find home directory\n");
    return NULL;
  }

  char* ret = NULL;
  catpath(&ret, h);
  catpath(&ret, "/.local/include");

  return ret;
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
