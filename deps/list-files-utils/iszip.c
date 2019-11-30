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

#include "iszip.h"

int iszip(const char* file) {
    if (extcmp(file, ".gz") == 0) {
        return(0);
    } else if (extcmp(file, ".lz4") == 0) {
        return(0);
    } else if (extcmp(file, ".zip") == 0) {
        return(0);
    }

    return(-1);
}

// vim: tabstop=2 shiftwidth=2 expandtab autoindent softtabstop=0

