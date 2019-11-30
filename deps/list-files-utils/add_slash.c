// created by: WestleyR
// email: westleyr@nym.hush.com
// https://github.com/WestleyR/list-files
// date: Nov 29, 2019
// version-1.0.0
//
// The Clear BSD License
//
// Copyright (c) 2019 WestleyR
// All rights reserved.
//
// This software is licensed under a Clear BSD License.
//

#include "add_slash.h"

int add_slash(char* path) {
    int len = strlen(path);
    if (path[len-1] != '/') {
        add_char_to_string(path, '/');
    }

    return(0);
}

// vim: tabstop=2 shiftwidth=2 expandtab autoindent softtabstop=0

