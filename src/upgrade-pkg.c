//
//  upgrade-pkg.c
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

#include "upgrade-pkg.h"

int loop_for_user_packages(const char* install_dir, const char* user_name) {
  char* user_packages_path = NULL;
  catpath(&user_packages_path, install_dir);
  catpath(&user_packages_path, user_name);

  DIR *dir;
  struct dirent *d;
  dir = opendir(user_packages_path);
  if (dir == NULL) {
    fprintf(stderr, "Failed to open: %s\n", user_packages_path);
    return 1;
  }

  // Open the main repo list
  repolist* rl = get_all_packages();

  // Loop through all installed packages by user name,
  // eg. ~/.gpack/installed/WestleyR.
  while ((d = readdir(dir)) != NULL) {
    if (*d->d_name != '.' && strcmp(d->d_name, "..") != 0) {
      // Create the package path, ie. WestleyR/srm
      char* usr_pkg = NULL;
      catpath(&usr_pkg, user_name);
      catpath(&usr_pkg, d->d_name);

      // Get the latest info on the package, like version.
      repo* r = get_obj_for_pkg(rl, usr_pkg);
      if (r == NULL) {
        print_errorf("package: %s does not exist in repolist. Skipping\n", usr_pkg);
        continue;
      }

      char* current_pkg_version = get_installed_pkg_version(user_name, d->d_name);
      char* latest_pkg_version = r->version;

      print_debugf("Checking package: %s...\n", d->d_name);

      print_debugf("Current version: %s\n", current_pkg_version);
      print_debugf("Latest verison:  %s\n", latest_pkg_version);

      if (strcmp(current_pkg_version, latest_pkg_version) != 0) {
        printf("I: package out-of-date: %s\n", usr_pkg);

        // First remove the pkg
        // TODO: this should be handled in the install_pkg options

        if (remove_pkg(usr_pkg) != 0) {
          fprintf(stderr, "Failed to remove pkg: %s\n", usr_pkg);
          return -1;
        }

        // Reinstall the package
        // TODO: error check
        if (install_pkg(noerror(), usr_pkg, true) != 0) {
          fprintf(stderr, "Failed to upgrade package: %s\n", usr_pkg);
          return -1;
        }
      }

      free(current_pkg_version);
      free(usr_pkg);
    }
  }

  closedir(dir);
  free(user_packages_path);
  repolist_destroy(rl);

  return 0;
}

int upgrade_pkg() {
  printf("I: Checking out-of-date packages...\n");

  char* install_dir = package_install_dir();
  // ~/.gpack/installed

  DIR *dir = opendir(install_dir);
  if (dir == NULL) {
    fprintf(stderr, "Failed to open: %s\n", install_dir);
    return 1;
  }

  // Loop through all installed packages, eg. ~/.gpack/installed.
  struct dirent *d;
  while ((d = readdir(dir)) != NULL) {
    if (*d->d_name != '.' && strcmp(d->d_name, "..") != 0) {
      print_debugf("Checking user name: %s...\n", d->d_name);
      loop_for_user_packages(install_dir, d->d_name);
    }
  }

  closedir(dir);
  free(install_dir);

  printf("I: Done\n");

  return 0;
}

// vim: tabstop=2 shiftwidth=2 expandtab autoindent softtabstop=0
