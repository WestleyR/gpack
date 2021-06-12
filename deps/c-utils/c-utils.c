// Created by: WestleyR
// email: westleyr@nym.hush.com
// Date: Apr 20, 2019
// https://github.com/WestleyR/c-utils
// version-1.0.0
//
// The Clear BSD License
//
// Copyright (c) 2019 WestleyR
// All rights reserved.
//
// This software is licensed under a Clear BSD License.
//

#include "c-utils.h"

void add_char_to_string(char* s, char c) {
    int len = strlen(s);
    s[len] = c;
    s[len+1] = '\0';
}

//
// End c-utils.c
//
