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
}

// print_package will print a package, with its version
int print_package(error* err, repolist* rl, const char* path, const char* name, int print_len) {
  print_debugf("funcall\n");

  DIR *dir;
  struct dirent *d;
  dir = opendir(path);
  if (dir == NULL) {
    error_printf(err, "failed to open: %s", path);
    return 1;
  }

  // Loop through all installed packages under the user
  // name path, eg. ~/.gpack/installed/WestleyR.
  while ((d = readdir(dir)) != NULL) {
    if (*d->d_name != '.' && strcmp(d->d_name, "..") != 0) {
      char* usr_pkg = NULL;
      catpath(&usr_pkg, name);
      catpath(&usr_pkg, d->d_name);

      // Print the package
      printf("%s", usr_pkg);

      // Spacing formatting
      for (int i = strlen(name) + strlen(d->d_name) + 1; i < print_len; i++) printf(" ");

      // Print the package version
      char *pkg_version = get_installed_pkg_version(name, d->d_name);
      printf(" %s", pkg_version);

      // Now check the "latest" version for that package
      repo* r = get_obj_for_pkg(rl, usr_pkg);
      if (r == NULL) {
        print_debugf("Failed get latest version for pkg: %s -> %s\n", name, d->d_name);
        printf("->%s", "error getting version");
      } else {
        if ((pkg_version != NULL) && (strcmp(r->version, pkg_version) != 0)) {
          // Versions do not match, update ready
          printf("->%s (upgradeable)", r->version);
        }
      }

      free(pkg_version);

      printf("\n");
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
    return 1;
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
int list_packages(error* err) {
  print_debugf("funcall\n");

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

  // Open the main repo list file, so we can
  // get each package version from it.
  repolist* rl = get_all_packages();
  if (rl == NULL) {
    // TODO: logger
    return -1;
  }

  // Now print all the packages
  while ((d = readdir(dir)) != NULL) {
    if (*d->d_name != '.' && strcmp(d->d_name, "..") != 0) {
      char* pkg = NULL;
      catpath(&pkg, d->d_name);

      char* full_path = NULL;
      catpath(&full_path, ppath);
      catpath(&full_path, d->d_name);

      print_debugf("full package path at: %s -> %s\n", pkg, full_path);

      print_package(err, rl, full_path, pkg, max_len);
      if (*err != NULL) {
        error_printf(err, "failed to print package: %s", full_path);
        return -1;
      }

      free(pkg);
      free(full_path);
    }
  }
  closedir(dir);

  free(ppath);

  repolist_destroy(rl);

  return 0;
}

// vim: tabstop=2 shiftwidth=2 expandtab autoindent softtabstop=0
