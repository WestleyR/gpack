//
//  update-pkg.c for gpack
//  https://github.com/WestleyR/gpack
//
// Created by WestleyR on 2019-06-21
// Source code: https://github.com/WestleyR/gpack
//
// Copyright (c) 2019-2021 WestleyR. All rights reserved.
// This software is licensed under a BSD 3-Clause Clear License.
// Consult the LICENSE file that came with this software regarding
// your rights to distribute this software.
//

#include "update-pkg.h"

int update_pkg() {
  char* repo_list = download_repo_index(true);
  free(repo_list);

  printf("I: Done\n");

  return(0);
}

// vim: tabstop=2 shiftwidth=2 expandtab autoindent softtabstop=0
