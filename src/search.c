//
//  search.c
//  gpack - https://github.com/WestleyR/gpack
//
// Created by WestleyR on Dec 25, 2019
// Source code: https://github.com/WestleyR/gpack
//
// Copyright (c) 2019-2021 WestleyR. All rights reserved.
// This software is licensed under a BSD 3-Clause Clear License.
// Consult the LICENSE file that came with this software regarding
// your rights to distribute this software.
//

#include "search.h"

int search_pkg(const char* pat, int print) {
  char* repo_file = download_repo_index(false);
  if (repo_file == NULL) {
    return -1;
  }

  repolist* rl = parse_repofile(repo_file);

  for (int i = 0; i < rl->repo_count; i++) {
    printf("%s\n\tDescription: %s\n\n", rl->repos[i]->name, rl->repos[i]->description);
  }

  repolist_destroy(rl);
  free(repo_file);

  return 0;
}

// vim: tabstop=2 shiftwidth=2 expandtab autoindent softtabstop=0
