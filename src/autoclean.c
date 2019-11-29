// Created by: WestleyR
// email: westleyr@nym.hush.com
// Date: Nov 23, 2019
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

#include "autoclean.h"

int find_link(char* symlink, const char* name) {
  char link_buff[256];
  link_buff[0] = '\0';

  ssize_t len = readlink(name, link_buff, sizeof(link_buff));
  if (len == -1) {
    perror("readlink");
    fprintf(stderr, "Unable to find link for: %s\n", name);
    return(-1);
  }

  symlink[0] = '\0';
  strcpy(symlink, link_buff);
  symlink[len] = '\0';

  return(0);
}

int autoclean() {
  char* installed_dir = get_bin();

  DIR *dir;
  struct dirent *d;
  dir = opendir(installed_dir);
  if (dir == NULL) {
    fprintf(stderr, "Failed to open: %s\n", installed_dir);
    return(1);
  }

  struct stat info;
  char full_file_path[256];
  full_file_path[0] = '\0';

  while ((d = readdir(dir)) != NULL) {
    if (*d->d_name != '.' && strcmp(d->d_name, "..") != 0) {
      strcpy(full_file_path, installed_dir);
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
        char full_link_path[strlen(installed_dir)+strlen(link_path)+1];
        full_link_path[0] = '\0';

        if (link_path[0] == '/') {
          strcpy(full_link_path, link_path);
        } else {
          strcpy(full_link_path, installed_dir);
          strcat(full_link_path, link_path);
        }

        if (access(full_link_path, F_OK) != 0) {
          // If the link is broken
          printf("%s: Link is broken\n", d->d_name);
          printf("Removing: %s\n", full_file_path);
          if (remove(full_file_path) != 0) {
            fprintf(stderr, "Failed to remove: %s\n", full_file_path);
            return(1);
          }
        } else {
          printf("%s: Link OK\n", d->d_name);
        }
        free(link_path);
      } else {
        fprintf(stderr, "%s: Is not a link, skipping\n", d->d_name);
      }
    }
  }

  closedir(dir);
  free(installed_dir);

  return 1;
}

// vim: tabstop=2 shiftwidth=2 expandtab autoindent softtabstop=0
