// Created by: WestleyR
// email: westleyr@nym.hush.com
// Date: Dec 22, 2019
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
#include <string.h>

int main(int argc, char **argv) {
//  if (argc <= 1) {
//    return(1);
//  }

  char line[256];
  char sha[256];

  while (fgets(line, sizeof(line), stdin)) {
//    printf("LINE: %s", line); 
    if (strstr(line, "sha") != NULL) {
      strcpy(sha, line);
      break;
    }
  }

  char *p;
  int c = 0;
  p = strtok (sha, "\"");
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

  return(0);
}

// vim: tabstop=2 shiftwidth=2 expandtab autoindent softtabstop=0
