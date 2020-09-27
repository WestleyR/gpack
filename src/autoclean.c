// Created by: WestleyR
// Email: westleyr@nym.hush.com
// Url: https://github.com/WestleyR/gpack
// Last modified date: 2020-09-26
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

#include "autoclean.h"

int clean_older_pkgs(int dry_run) {
  print_debugf("%s()\n", __func__);

  // Directory tree:
  //   installed_dir = ~/.gpack/installed
  //
  //   installed_dir/<username>/<pkgname>/version.gpack
  //                                      1.0.0/
  //                                      1.0.1/

  char* installed_dir = get_package_prefix();
  if (installed_dir == NULL) {
    fprintf(stderr, "%s() failed to get install dir\n", __func__);
    return -1;
  }
 
  DIR *dir;
  struct dirent *d;
  dir = opendir(installed_dir);
  if (dir == NULL) {
    fprintf(stderr, "Failed to open: %s\n", installed_dir);
    return -1;
  }

  struct stat info;
  char full_file_path[256];
  full_file_path[0] = '\0';

  while ((d = readdir(dir)) != NULL) {
    if (*d->d_name != '.' && strcmp(d->d_name, "..") != 0) {

      char* full_file_path = path_join(installed_dir, "");
      full_file_path = path_join(full_file_path, d->d_name);

      print_debugf("opening file: %s\n", full_file_path);
      if (lstat(full_file_path, &info) != 0) {
        perror("lstat");
        printf("error: unable to open stat on: %s\n", full_file_path);
        free(full_file_path);
        continue;
      }


      free(full_file_path);
    }
  }
 

  free(installed_dir);

  return 0;
}

int helper_autoclean(int dry_run) {
  // For ~/.local/bin
  char* bin_dir = get_bin();
  if (bin_dir == NULL) {
    fprintf(stderr, "Failed to get gpack bin dir\n");
    return(1);
  }
  print_debugf("Cleaning bin dir: %s\n", bin_dir);
  if (autoclean(bin_dir, dry_run) != 0) {
    return(1);
  }
  free(bin_dir);

  // For ~/.local/lib
  char* lib_dir = get_lib_dir();
  if (lib_dir == NULL) {
    fprintf(stderr, "Failed to get gpack lib dir\n");
    return(1);
  }
  print_debugf("Cleaning lib dir: %s\n", lib_dir);
  if (autoclean(lib_dir, dry_run) != 0) {
    return(1);
  }
  free(lib_dir);

  // For ~/.local/include
  char* include_dir = get_include_dir();
  if (include_dir == NULL) {
    fprintf(stderr, "Failed to get gpack include dir\n");
    return(1);
  }
  print_debugf("Cleaning include dir: %s\n", include_dir);
  if (autoclean(include_dir, dry_run) != 0) {
    return(1);
  }
  free(include_dir);

  // Now clean the packages
  if (clean_older_pkgs(dry_run) != 0) {
    return 1;
  }

  return(0);
}

int autoclean(const char* clean_dir, int dry_run) {
  DIR *dir;
  struct dirent *d;
  dir = opendir(clean_dir);
  if (dir == NULL) {
    fprintf(stderr, "Failed to open: %s\n", clean_dir);
    return(1);
  }

  struct stat info;
  char full_file_path[256];
  full_file_path[0] = '\0';

  while ((d = readdir(dir)) != NULL) {
    if (*d->d_name != '.' && strcmp(d->d_name, "..") != 0) {
      strcpy(full_file_path, clean_dir);
      strcat(full_file_path, "/");
      strcat(full_file_path, d->d_name);

      if (lstat(full_file_path, &info) != 0) {
        perror("lstat");
        printf("error: unable to open stat on: %s\n", full_file_path);
        exit(20);
      }

      if (S_ISLNK(info.st_mode)) {
        char *link_path;
        link_path = (char*) malloc(256 * sizeof(char));

        int err = find_link(link_path, full_file_path);
        if (err != 0) {
          strcpy(link_path, "failed to get symlink");
        }
        char full_link_path[strlen(clean_dir)+strlen(link_path)+1];
        full_link_path[0] = '\0';

        if (link_path[0] == '/') {
          strcpy(full_link_path, link_path);
        } else {
          strcpy(full_link_path, clean_dir);
          strcat(full_link_path, link_path);
        }

        if (access(full_link_path, F_OK) != 0) {
          // If the link is broken
          print_debugf("%s: Link is broken\n", d->d_name);
          if (dry_run == 1) {
            printf("I: Would remove broken link: %s\n", full_file_path);
          } else {
            printf("I: Removing broken link: %s\n", full_file_path);
            if (remove(full_file_path) != 0) {
              fprintf(stderr, "Failed to remove: %s\n", full_file_path);
              return(1);
            }
          }
        } else {
          print_debugf("%s: Link OK\n", d->d_name);
        }
        free(link_path);
      } else {
        print_debugf("%s: Is not a link, skipping\n", d->d_name);
      }
    }
  }

  closedir(dir);

  return(0);
}

// vim: tabstop=2 shiftwidth=2 expandtab autoindent softtabstop=0
