//
//  config.c for gpack
//  https://github.com/WestleyR/gpack
//
// Created by WestleyR on 2021-06-09
// Source code: https://github.com/WestleyR/gpack
//
// Copyright (c) 2021 WestleyR. All rights reserved.
// This software is licensed under a BSD 3-Clause Clear License.
// Consult the LICENSE file that came with this software regarding
// your rights to distribute this software.
//

#include "config.h"


int show_config_help() {
  printf("Currently the package repo list is in a github repo, but\n");
  printf("I think you should be able to to configure a url for a text\n");
  printf("file of a list of all the packages, with the urls. That list\n");
  printf("will be fetched (and cached) whenever you check for updates.\n");
  printf("\n");
  printf("So, you might have a ~/.config/wst.gpack/config.ini to hold the\n");
  printf("repo url list. When first running the gpack binary (and that file\n");
  printf("is empty), gpack will use the default repo list.\n");
  printf("\n");
  printf("\n");

  return 0;
}


// vim: tabstop=2 shiftwidth=2 expandtab autoindent softtabstop=0
