// Created by: WestleyR
// email: westleyr@nym.hush.com
// Date: Jun 22, 2019
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

#include "remove-pkg.h"
#include "config.h"

#include "logger/logger.h"

int remove_pkg(char *pkg) {
    print_debugf("Removing: %s\n", pkg);

    char cmd[256];

    strcat(cmd, REMOVE_PKG_NAME);
    strcat(cmd, " ");
    strcat(cmd, pkg);
    strcat(cmd, " pkg.list");

    return(system(cmd));
}

//
// End update-pkg.c
//
