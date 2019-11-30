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

#include "extcmp.h"

int extcmp(const char *string, const char* ext) {
    string = strrchr(string, '.');

    if (string != NULL) {
        return(strcmp(string, ext));
    }

    return(-1);
}

// vim: tabstop=2 shiftwidth=2 expandtab autoindent softtabstop=0

