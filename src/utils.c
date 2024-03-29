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

char* get_repolist_url() {
  char* url = "https://gist.githubusercontent.com/WestleyR/81b31029e8c02b5434ee8f9a4217af04/raw/repolist.ini";
  return url;
}

char* get_gpack_arch() {
  struct utsname m;
  if (uname(&m) != 0) {
    // TODO: use a logger package here!
    fprintf(stderr, "%s:%s():%d: failed to run uname: ", __FILE__, __func__, __LINE__);
    perror("uname");
    exit(255);
  }


  if (strcmp(m.sysname, "Darwin") == 0) {
    if (strcmp(m.machine, "x86_64") == 0) {
      return "darwin_x86";
    } else {
      fprintf(stderr, "Only Darwin x86 is supported\n");
      exit(1);
    }
  } else if (strcmp(m.sysname, "Linux") == 0) {
    if (strcmp(m.machine, "x86_64") == 0) {
      return "linux_x86_64";
    } else {
      fprintf(stderr, "Only Linux x86_64 is supported\n");
      exit(1);
    }
  }

  fprintf(stderr, "%s:%s():%d: failed to get system infomation\n", __FILE__, __func__, __LINE__);

  return NULL;
}

char* get_binary_sha(const char* arch) {
  if (strcmp(arch, "darwin_x86") == 0) {
    return "darwin_x86_sha1";
  } else if (strcmp(arch, "linux_x86_64") == 0) {
    return "linux_x86_64_sha1";
  } else if (strcmp(arch, "armv6l") == 0) {
    return "armv6l_sha1";
  }

  fprintf(stderr, "%s:%s():%d: failed to get system infomation\n", __FILE__, __func__, __LINE__);

  return NULL;
}

char* get_installdir_for_user_and_version(const char* usr_pkg, const char* version) {
  char* path =  NULL;

  char* h = getenv("HOME");
  if (h == NULL) {
    fprintf(stderr, "Cant find home directory\n");
    return(NULL);
  }

  catpath(&path, h);
  catpath(&path, ".gpack/installed");
  catpath(&path, usr_pkg);
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

// Returns ~/.cache/wst.gpack/repo-list.ini
char* get_repo_index_file() {
  char* h = getenv("HOME");
  if (h == NULL) {
    fprintf(stderr, "Cant find home directory\n");
    return NULL;
  }

  char* path = NULL;
  catpath(&path, h);
  catpath(&path, ".cache/wst.gpack/repo-list.ini");

  return path;
}

// End new functions!!!

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

// vim: tabstop=2 shiftwidth=2 expandtab autoindent softtabstop=0
