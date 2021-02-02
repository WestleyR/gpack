//
//  list.c
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

#include "list.h"

int ensure_installed_files(const char* user_name, const char* pkg) {
  // TODO: need code here

  // Maybe have a `installed-files.ini` file in `~/.gpack/database/installed-files.ini`, which
  // contains all the installed packages and the files they should have installed, along with
  // a checksum for each file. Which will also be verified when running `gpack list`.

  return 0;

/*
  char* pkg_listmap = get_listmap_for_pkg(user_name, pkg);

  FILE* fp = fopen(pkg_listmap, "r");

  free(pkg_listmap);

  if (fp == NULL) {
    // Failed to open list map
    print_verbosef("%s/%s does not have a checksum list. You should reinstall that package\n", user_name, pkg);
    return 0;
  }

  return check_crc32_file(fp, SSUM_BLOCK_SIZE, NULL, NULL);
*/
  //  char** installed_files = get_installed_files_from_map(pkg_listmap, 1);
  //  char** installed_checksum = get_installed_files_from_map(pkg_listmap, 2);
  //
  //  if (installed_files != NULL) {
  //    printf("HELLO WORLD OUTPUT: %s\n", installed_files[0]);
  //    printf("HELLO WORLD OUTPUT: %s\n", installed_checksum[0]);
  //
  //    printf("\n");
  //
  //    printf("HELLO WORLD OUTPUT: %s\n", installed_files[1]);
  //    printf("HELLO WORLD OUTPUT: %s\n", installed_checksum[1]);
  //
  //    free(installed_files);
  //    free(installed_checksum);
  //  }
}

// print_package will print a package, with its version
int print_package(const char* path, const char* name, int print_len) {
  DIR *dir;
  struct dirent *d;
  dir = opendir(path);
  if (dir == NULL) {
    fprintf(stderr, "Failed to open: %s\n", path);
    return 1;
  }

  // Loop through all installed packages under the user
  // name path, eg. ~/.gpack/installed/WestleyR.
  while ((d = readdir(dir)) != NULL) {
    if (*d->d_name != '.' && strcmp(d->d_name, "..") != 0) {
      int filesOK = 0;
      if (ensure_installed_files(name, d->d_name) != 0) {
        print_debugf("%s/%s failed checksum\n", name, d->d_name);
        filesOK = 1;
      }

      // Print the package
      printf("%s/%s", name, d->d_name);

      // Spacing formatting
      for (int i = strlen(name) + strlen(d->d_name) + 1; i < print_len; i++) printf(" ");

      // Print the package version
      char *pkg_version = get_installed_pkg_version(name, d->d_name);
      printf(" %s", pkg_version);

      // Now check the "latest" version for that package
      char* latest_version = get_latest_version_for_pkg(name, d->d_name);

      if (strcmp(latest_version, pkg_version) != 0) {
        // Versions do not match, proboly an update
        printf("->%s (upgradeable)", latest_version);
      }

      free(pkg_version);
      free(latest_version);

      if (filesOK != 0) {
        printf(" %s[installed files were overidden]%s please re-install", BOLDRED, COLORRESET);
      }

      printf("\n");

      // TODO: FIXME!
      // Print if its up-to-date
    }
  }
  closedir(dir);

  return 0;
}

// get_max_len_of_package_name will get the max string len of a package user/name.
// Eg. WestleyR/list-files.
int get_max_len_of_package_name(const char* user_path, const char* user_name) {
  DIR *dir;
  struct dirent *d;

  print_debugf("Opening from: %s\n", user_path);
  dir = opendir(user_path);
  if (dir == NULL) {
    fprintf(stderr, "Failed to open: %s\n", user_path);
    return(1);
  }

  int max_package_len = 0;

  // Get the max package name length
  while ((d = readdir(dir)) != NULL) {
    if (*d->d_name != '.' && strcmp(d->d_name, "..") != 0) {
      print_debugf("Getting max len for: %s and: %s\n", user_name, d->d_name);
      int len = strlen(user_name);
      len += strlen(d->d_name);
      if (len > max_package_len) max_package_len = len;
    }
  }
  closedir(dir);

  print_debugf("max package len: %d\n", max_package_len);

  return max_package_len;
}

// list_packages will list all installed packages
int list_packages() {
  char* ppath = package_install_dir();

  DIR *dir;
  struct dirent *d;
  dir = opendir(ppath);
  if (dir == NULL) {
    fprintf(stderr, "Failed to open: %s\n", ppath);
    return 1;
  }

  int max_len = 0;

  // Get the max package len
  while ((d = readdir(dir)) != NULL) {
    if (*d->d_name != '.' && strcmp(d->d_name, "..") != 0) {
      char* pkg = NULL;
      catpath(&pkg, d->d_name);

      char* full_path = NULL;
      catpath(&full_path, ppath);
      catpath(&full_path, d->d_name);

      int len = get_max_len_of_package_name(full_path, d->d_name);

      free(full_path);
      free(pkg);
      if (len > max_len) max_len = len;
    }
  }
  rewinddir(dir);

  // Give a little extra
  max_len += 2;

  print_debugf("Max package name len: %d\n", max_len);

  while ((d = readdir(dir)) != NULL) {
    if (*d->d_name != '.' && strcmp(d->d_name, "..") != 0) {
      char* pkg = NULL;
      catpath(&pkg, d->d_name);

      char* full_path = NULL;
      catpath(&full_path, ppath);
      catpath(&full_path, d->d_name);

      print_package(full_path, pkg, max_len);

      free(pkg);
      free(full_path);
    }
  }
  closedir(dir);

  free(ppath);

  return 0;
}

// vim: tabstop=2 shiftwidth=2 expandtab autoindent softtabstop=0
