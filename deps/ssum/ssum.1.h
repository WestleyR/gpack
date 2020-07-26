// created by: WestleyR
// email: westleyr@nym.hush.com
// https://github.com/WestleyR/ssum
// date: Dec 21, 2019
// version: na; see ssum.1.c
//
// The Clear BSD License
//
// Copyright (c) 2019 WestleyR
// All rights reserved.
//
// This software is licensed under a Clear BSD License.
//

#ifndef INCLUDE_SSUM_H
#define INCLUDE_SSUM_H
#define SSUM_HEADERFILE_VERSION "v1.1.0, Dec 21, 2019"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//
// Library API/functions
//

//
// ## Defines
//

#ifndef SSUM_BLOCK_SIZE
#define SSUM_BLOCK_SIZE 20
#endif
//
// This is the block size when reading from a file.
//


//
// Function calls
//

const char* libssum_version();
// ### Parameters
// 
// Non.
// 
// ### Returns
// 
// The libssum version, like `v3.0.0, Dec 19, 2019`.
// 

unsigned int crc32_hash(const unsigned char *message, int msg_len);
// ### Parameters
// 
// `message` is a string. `msg_len` is the length of the message/string.
// 
// ### Returns
// 
// The crc for the given `message`.
//

unsigned int crc32_file(FILE* fp, int block_size);
// ### Parameters
// 
// `fp` is the open file to read from, read it as a binary file (`"rb"`).
// `block_size` is the size of the block to read.
// 
// ### Returns
// 
// The crc for the contents of the file.
//

int check_crc32_file(FILE* fp, int block_size);
// ### Parameters
// 
// `fp` is the open file that contains the hash for a file. Open the file in read
// mode, and non-binary (`"r"`). `block_size` is the size of the block to read.
// 
// ### Returns
// 
// Returns `0` (zero) if the checksum and file match. Returns `1` if it does not.
// And `-1` if theres a other error.
//

#endif // INCLUDE_SSUM_H

// vim: tabstop=2 shiftwidth=2 expandtab autoindent softtabstop=0
