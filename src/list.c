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

#include "list.h"

int ensure_installed_files(const char* user_name, const char* pkg) {

  char* pkg_listmap = get_listmap_for_pkg(user_name, pkg);

  FILE* fp = fopen(pkg_listmap, "r");

  free(pkg_listmap);

  if (fp == NULL) {
    // Failed to open list map
    print_verbosef("%s/%s does not have a checksum list. You should reinstall that package\n", user_name, pkg);
    return 0;
  }

  return check_crc32_file(fp, SSUM_BLOCK_SIZE, NULL, NULL);

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
    return(1);
  }

  // Loop through all installed packages under the user
  // name path, eg. ~/.gpack/installed/WestleyR.
  while ((d = readdir(dir)) != NULL) {
    if (*d->d_name != '.' && strcmp(d->d_name, "..") != 0) {


      //      char* main_pkg_dir = get_package_dir();
      //      char* package_script = path_join(main_pkg_dir, name);
      //      package_script = path_join(package_script, d->d_name);
      //
      //      print_verbosef("package source installer: %s\n", package_script);
      //
      //      free(main_pkg_dir);
      //      free(package_script);

      int filesOK = 0;
      if (ensure_installed_files(name, d->d_name) != 0) {
        print_debugf("%s/%s failed checksum\n", name, d->d_name);
        filesOK = 1;
      }

      // Print the package
      char *pkg_version = get_installed_pkg_version(path, d->d_name);
      printf("%s/%s", name, d->d_name);

      // Spacing formatting
      for (int i = strlen(name) + strlen(d->d_name) + 1; i < print_len; i++) printf(" ");

      // Print the package version
      printf(" %s", pkg_version);
      free(pkg_version);

      if (filesOK != 0) {
        printf(" %s[installed files were overidden]%s please re-install", BOLDRED, COLORRESET);
      }

      printf("\n");

      // Print if its up-to-date
      // TODO: FIXME!
      //char* vlable = compare_pkg_version(
    }
  }
  closedir(dir);

  return(0);
}

// get_max_len_of_package_name will get the max string len of a package user/name.
// Eg. WestleyR/list-files.
int get_max_len_of_package_name(const char* user_path, const char* user_name) {
  DIR *dir;
  struct dirent *d;

  //print_debugf("Opening from: %s\n", user_path);
  dir = opendir(user_path);
  if (dir == NULL) {
    fprintf(stderr, "Failed to open: %s\n", user_path);
    return(1);
  }

  int max_package_len = 0;

  // Determen the max package name length
  while ((d = readdir(dir)) != NULL) {
    if (*d->d_name != '.' && strcmp(d->d_name, "..") != 0) {
      print_debugf("Getting max len for: %s and: %s\n", user_path, d->d_name);
      int len = strlen(user_name);
      len += strlen(d->d_name);
      if (len > max_package_len) max_package_len = len;
    }
  }

  print_debugf("max package len: %d\n", max_package_len);

  return max_package_len;
}

// list_packages will list all installed packages
int list_packages() {
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

  int max_len = 0;

  // Get the max package len
  while ((d = readdir(dir)) != NULL) {
    if (*d->d_name != '.' && strcmp(d->d_name, "..") != 0) {
      strcpy(pkg, d->d_name);

      // TODO: use path_join function here
      char* full_path = path_join(ppath, "");
      full_path = path_join(full_path, d->d_name);

      int len = get_max_len_of_package_name(full_path, d->d_name);
      free(full_path);
      if (len > max_len) max_len = len;
    }
  }
  rewinddir(dir);

  // Give a little extra
  max_len += 2;

  print_debugf("Max package name len: %d\n", max_len);

  while ((d = readdir(dir)) != NULL) {
    if (*d->d_name != '.' && strcmp(d->d_name, "..") != 0) {
      strcpy(pkg, d->d_name);

      // TODO: use path_join function here
      strcpy(full_path, ppath);
      strcat(full_path, d->d_name);

      print_package(full_path, pkg, max_len);
    }
  }
  closedir(dir);

  free(ppath);

  return 0;
}

// vim: tabstop=2 shiftwidth=2 expandtab autoindent softtabstop=0
