//
//  errors.c
//  errors - https://github.com/??? (will be a c library)
//
// Created by WestleyR on 2021-08-29
// Source code: https://github.com/WestleyR/gpack
//
// Copyright (c) 2021 WestleyR. All rights reserved.
// This software is licensed under a BSD 3-Clause Clear License.
// Consult the LICENSE file that came with this software regarding
// your rights to distribute this software.
//

// See this included file for documentation.
#include "errors.h"

int error_printf(error* err, const char* fmt, ...) {
  char* msg = NULL;
  int arg_len;
  int init_size = strlen(fmt) + 40;

  // Make sure to only malloc enought, and not too much
  while (1) {
    va_list args;
    va_start(args, fmt);

    free(msg);
    msg = malloc(init_size);
    arg_len = vsprintf(msg, fmt, args);

    if (arg_len < init_size) {
      break;
    }
    init_size += 20;

    va_end(args);
  }

  if (*err == NULL) {
    error new_error = malloc(strlen(msg) + 2);
    strcpy(new_error, msg);

    *err = new_error;
    return 0;
  }

  char* old = strdup(*err);

  free(*err);

  char* new_error = malloc(strlen(msg) + strlen(old) + 4);

  int i = 0;
  while (*msg != '\0') {
    new_error[i] = *msg;
    msg++;
    i++;
  }

  new_error[i] = ':';
  new_error[i+1] = ' ';
  new_error[i+2] = '\0';

  strcat(new_error, old);

  *err = new_error;

  return 0;
}

// error_clear resets the error message.
int error_clear(error* err) {
  if (*err != NULL) {
    free(*err);
  }
  *err = NULL;

  return 0;
}

int iserror(error* err) {
  return *err != NULL;
}

error* noerror() {
  error* no_err = malloc(0);
  return no_err;
}

// vim: tabstop=2 shiftwidth=2 expandtab autoindent softtabstop=0
