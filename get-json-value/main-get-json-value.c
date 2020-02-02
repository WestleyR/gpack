// Created by: WestleyR
// Email(s): westleyr@nym.hush.com
// Last modifyed date: Jan 31, 2020
// This file version-1.0.0
//
// This file is part of the gpack software:
// https://github.com/WestleyR/gpack
//
// Which that software and this file is licensed under:
//
// The Clear BSD License
//
// Copyright (c) 2019-2020 WestleyR
// All rights reserved.
//
// This software is licensed under a Clear BSD License.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
  char* search;
  search = (char*) malloc(200 * sizeof(char));
  if (search == NULL) {
    fprintf(stderr, "Malloc failed\n");
    return(1);
  }

  strcpy(search, "sha");

  if (argc > 1) {
    strcpy(search, argv[1]);
  }

  char line[256];
  char raw_sha[128];
  int got_line = 0;

  while (fgets(line, sizeof(line), stdin)) {
    if (strstr(line, search) != NULL) {
      // Cant use break here since curl will print a warning:
      // (23) Failed writing body
      if (got_line == 0) {
        strcpy(raw_sha, line);
        got_line = 1;
      }
    }
  }

  char* sha;
  sha = (char*) malloc(128 * sizeof(char));
  if (sha == NULL) {
    fprintf(stderr, "FAIL: malloc failed\n");
    return(1);
  }

  char *p;
  int c = 0;
  p = strtok(raw_sha, "\"");
  while (p != NULL) {
    //printf("%s -> %d\n", p, c);
    if (c == 3) {
      strcpy(sha, p);
      break;
    }
    p = strtok(NULL, "\"");
    c++;
  }

  printf("%s\n", sha);
  free(sha);
  free(search);

  return(0);
}

// vim: tabstop=2 shiftwidth=2 expandtab autoindent softtabstop=0
