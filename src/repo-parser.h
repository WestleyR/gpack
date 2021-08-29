//
//  repo-parser.h for gpack
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

#ifndef INCLUDE_REPO_PARSER_H
#define INCLUDE_REPO_PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "bool.h"
#include "utils.h"
#include "ini.h"
#include "logger/logger.h"

typedef struct repo repo;
typedef struct repolist repolist;

struct repo {
  char* name;
  char* description;
  char* homepage;
  char* download_url; // will only collect the download for the current arch
  char* sha1;
  char* bin_files; // right now, can only handle one install file
  char* version;
};

struct repolist {
  struct repo** repos;
  int repo_count;
};

// download_repo_index will download the index file from the specified (todo)
// location or the default URL. If file already exists, will not download unless
// update is true.
char* download_repo_index(bool update);


// get_all_packages is a helper function to return all avalible packages
// in a repolist* struct. Return value must be freed with repolist_destroy().
// TODO: not memory friendly.
repolist* get_all_packages();

repo* get_obj_for_pkg(repolist* rl, const char* pkg);
ini_t* read_ini_file(const char* path);
repolist* parse_repofile(const char* filepath);
int repolist_destroy(repolist* rp);

#endif // INCLUDE_REPO_PARSER_H

// vim: tabstop=2 shiftwidth=2 expandtab autoindent softtabstop=0
