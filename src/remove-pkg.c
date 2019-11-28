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

#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

#include "remove-pkg.h"
#include "config.h"

#include "logger/logger.h"

int remove_pkg(char *pkg) {
    print_debugf("Removing: %s\n", pkg);

    char cmd[256];
    cmd[0] = '\0';

    char pkg_file[200];
    pkg_file[0] = '\0';

    strcpy(pkg_file, "installed/");
    strcat(pkg_file, pkg);

    strcpy(cmd, "rm -rf ${HOME}/.gpack/installed/");
    strcat(cmd, pkg);

    char installed_pkg[256];
    installed_pkg[0] = '\0';

    char* h = getenv("HOME");

    strcpy(installed_pkg, h);
    strcat(installed_pkg, "/.gpack/installed/");
    strcat(installed_pkg, pkg);

    struct stat sb;
    if (stat(installed_pkg, &sb) != 0 || !S_ISDIR(sb.st_mode)) {
        printf("%s: is not installed\n", pkg);
        return 1;
    }

    printf("About to run: %s\n", cmd);

    system("sleep 3s");

    system(cmd);

    return(0);
}

//
// End update-pkg.c
//
