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
#include "cerror.h"

#ifdef CERROR_DEBUG
#define cerror_debugf(...) printf(__VA_ARGS__)
#else
#define cerror_debugf(...)
#endif

void cleanup();

typedef struct {
  void** pt;
  int len;
  int allocated_len;
} pt;

pt ptracker = {NULL, 0, 20};

int set_atexit_cleanup = 0;

void add_ptr(void* ptr) {
  // Check if we need to (re)alloc space
  if (ptracker.pt == NULL) {
    ptracker.pt = (void**) malloc(sizeof(void*) * ptracker.allocated_len);

    // Make all new spots NULL, otherwise valgrind will error
    for (int i = 0; i < ptracker.allocated_len; i++) {
      ptracker.pt[i] = NULL;
    }
  }

  if (ptracker.allocated_len - 2 <= ptracker.len) {
    cerror_debugf("REALLOCATED: %d\n", ptracker.allocated_len);
    ptracker.allocated_len += 20;
    ptracker.pt = realloc(ptracker.pt, sizeof(void*) * ptracker.allocated_len);

    // Make all new spots NULL, otherwise valgrind will error
    for (int i = ptracker.allocated_len - 20; i < ptracker.allocated_len; i++) {
      ptracker.pt[i] = NULL;
    }
  }

  cerror_debugf("ADDING: %p:%d\n", ptr, ptracker.len);
  ptracker.pt[ptracker.len] = ptr;
  ptracker.len++;

  if (set_atexit_cleanup == 0) {
    atexit(cleanup);
    set_atexit_cleanup = 1;
  }
}

void remove_ptr(void* ptr) {
  for (int i = ptracker.len; i >= 0; i--) {
    if (ptracker.pt[i] == ptr) {
      cerror_debugf("REMOVING_FOUND_PTR: %p\n", ptr);
      ptracker.pt[i] = NULL;
      break;
    }
  }
}

cerror new_cerror() {
  cerror err;
  err.err = NULL;
  err.stack_alloc = 20;
  err.stack_trace = malloc(sizeof(char*) * err.stack_alloc);
  err.stack_len = 0;
  err.len = 0;
  err.empty = 0;

  add_ptr(err.stack_trace);

  return err;
}

char* no_err = "no error";

void cleanup() {
  int skips[ptracker.len + 2];
  int skip_len = 0;

  for (int i = ptracker.len; i >= 0; i--) {
    for (int b = i+1; b < ptracker.len; b++) {
      cerror_debugf("CHECK i=%d b=%d -> %p\n", i, b, ptracker.pt[i]);
      if (ptracker.pt[i] == ptracker.pt[b]) {
        cerror_debugf("SKIP i=%d b=%d\n", i, b);
        skips[skip_len] = i;
        skip_len++;
        break;
      }
    }
  }

  for (int i = 0; i < ptracker.len; i++) {
    int skip = 0;
    for (int b = 0; b < skip_len; b++) {
      if (skips[b] == i) {
        skip = 1;
        break;
      }
    }
    if (skip == 0) {
      free(ptracker.pt[i]);
    }
  }
  free(ptracker.pt);
}

int add_stack_trace(cerror* err, const char* file, const char* func, int line) {
  int init_size = strlen(file) + strlen(func) + 1000; // TODO: get len of int
  char* trace_msg = (char*) malloc(init_size);

  // TODO: get the write size and compare with malloc len
  sprintf(trace_msg, "%s()\n\t%s on line: %d", func, file, line);

  // Check if we need to (re)alloc space
  if (err->stack_trace == NULL) {
    // Should never get here since we alloc this on new_cerror()
    err->stack_trace = (char**) malloc(sizeof(char*) * err->stack_alloc);
    add_ptr(err->stack_trace);
  }

  // Alloc more space if needed
  if (err->stack_alloc - 2 <= err->stack_len) {
    cerror_debugf("REALLOCATED_STACK: %d\n", err->stack_alloc);
    err->stack_alloc += 20;

    // Remove the old pointer
    remove_ptr(err->stack_trace);

    // Allocate the new bigger pointer
    err->stack_trace = realloc(err->stack_trace, sizeof(char*) * err->stack_alloc);

    // Re-add this new bigger pointer to the list
    add_ptr(err->stack_trace);
  }

  err->stack_trace[err->stack_len] = trace_msg;
  add_ptr(err->stack_trace[err->stack_len]);
  err->stack_len++;

  return 0;
}

int cerror_printf(const char* file, const char* func, int line, cerror* err, const char* fmt, ...) {
  if (err == (cerror*)no_err) {
    return 4;
  }

  add_stack_trace(err, file, func, line);

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

  if (err->err == NULL) {
    char* init_error = (char*) malloc(strlen(msg) + 2);
    strcpy(init_error, msg);
    err->err = init_error;
    add_ptr(init_error);

    free(msg);
    return 0;
  }

  char* old = strdup(err->err);

  err->err = NULL;

  char* new_error = malloc(strlen(msg) + strlen(old) + 4);

  add_ptr(new_error);

  int i = 0;
  i = strlen(msg);
  strcpy(new_error, msg);
  free(msg);

  new_error[i] = ':';
  new_error[i+1] = ' ';
  new_error[i+2] = '\0';

  strcat(new_error, old);

  free(old);

  err->err = new_error;

  return 0;
}

int print_stack_trace(cerror err, FILE* stream) {
  fprintf(stream, "STACK_TRACE [%d]: %s\n", err.stack_len, err.err);

  for (int i = 0; i < err.stack_len; i++) {
    fprintf(stream, "%s\n", err.stack_trace[i]);
  }

  return 0;
}

// error_clear resets the error message.
int error_clear(cerror* err) {
  err->err = NULL;
  err->len = 0;
  err->empty = 0;

  return 0;
}

int iserror(cerror* err) {
  return err->err != NULL;
}

void* noerror() {
  return no_err;
}

// vim: tabstop=2 shiftwidth=2 expandtab autoindent softtabstop=0
