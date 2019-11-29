// Created by: WestleyR
// email: westleyr@nym.hush.com
// Date: Jun 22, 2019
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

#include "reinstall-pkg.h"

int reinstall_pkg(const char *pkg) {
  printf("I: Reinstalling: %s\n", pkg);

  if (remove_pkg(pkg) != 0) {
    fprintf(stderr, "Failed to remove: %s\n", pkg);
    return(1);
  }

  if (install_pkg(pkg) != 0) {
    fprintf(stderr, "Failed to reinstall: %s\n", pkg);
    return(1);
  }

  printf("I: Done\n");

  return(0);
}

// vim: tabstop=2 shiftwidth=2 expandtab autoindent softtabstop=0
