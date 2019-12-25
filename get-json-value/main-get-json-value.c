// Created by: WestleyR
// email: westleyr@nym.hush.com
// Date: Dec 24, 2019
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
  //if (argc <= 1) {
  //  return(1);
  //}

  char line[256];
  char raw_sha[128];
  int got_line = 0;

  while (fgets(line, sizeof(line), stdin)) {
    if (strstr(line, "sha") != NULL) {
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

  return(0);
}

// vim: tabstop=2 shiftwidth=2 expandtab autoindent softtabstop=0
