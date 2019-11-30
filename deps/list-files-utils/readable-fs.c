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

#include "readable-fs.h"

char* readable_fs(double bytes) {
    int i = 0;
    char* buf;
    float size = bytes;
    buf = (char*) malloc(10 * sizeof(char));
    const char* units[] = {"B", "KB", "MB", "GB", "TB", "PB", "EB", "ZB", "YB"};

    while (size > 1024) {
        size /= 1024;
        i++;
    }
    sprintf(buf, "%.*f %s", i, size, units[i]);

    return(buf);
}

// vim: tabstop=2 shiftwidth=2 expandtab autoindent softtabstop=0
