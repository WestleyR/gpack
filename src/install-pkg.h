//
//  install-pkg.h
//  gpack - simple, fast non-root (user) package manager.
//
// Created by WestleyR on Jun 16, 2019
// Source code: https://github.com/WestleyR/gpack
//
// Copyright (c) 2019-2021 WestleyR. All rights reserved.
// This software is licensed under a BSD 3-Clause Clear License.
// Consult the LICENSE file that came with this software regarding
// your rights to distribute this software.
//

#ifndef INSTALL_PKG_H
#define INSTALL_PKG_H

#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <libgen.h>

#include "catpath.h"
#include "bool.h"
#include "remove-pkg.h"
#include "utils.h"
#include "reader.h"
#include "cache.h"
#include "logger/logger.h"
#include "repo-parser.h"

// Install options
const static int GPK_INSTALL_OVERIDE = 1;
const static int GPK_INSTALL_COMPILE_BUILD = 2; // no longer used
const static int GPK_INSTALL_MAX_OPTS = 3; // +1 extra

// The terminator for the options
const static int GPK_OPTS_END = 0;

typedef int gpk_install_opts[];

//**********
// Functions
//**********


int install_pkg(const char* pkg, bool force);

//int install_pkg(const char* pkg, gpk_install_opts opts);
/*
install_pkg() will take a package string (like: "WestleyR/srm"), and some install
options. The opts must be NULL, or terminated with GPK_OPTS_END (int 0). Returns
non-zero if an error occured, and the error will (should) be printed to stderr.

install_pkg() also takes care of caching.
TODO: cache should be cleaned every 3 days or soo

As an example, this function call should look like:

  int rc = install_pkg("WestleyR/srm", NULL);

Or:

  gpk_install_opts opts = {GPK_INSTALL_OVERIDE, GPK_OPTS_END};
  int rc = install_pkg("WestleyR/srm", opts);

Always make sure that you terminate the opts with GPK_OPTS_END, or 0.
*/

#endif // INSTALL_PKG_H

// vim: tabstop=2 shiftwidth=2 expandtab autoindent softtabstop=0
