// Created by: WestleyR
// email: westleyr@nym.hush.com
// Date: Jun 16, 2019
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

#include "main-gpack.h"

#include "logger/logger.h"

char* SCRIPT_NAME;

char* help_sort() {
    char* sort_help = "OPTIONS:\n\
  -h, --help      : print help menu.\n\
  -v, --verbose   : verbose.\n\
  -d, --debug     : debug output.\n\
  -V, --version   : print version.";

    return(sort_help);
}

void help_menu() {
    printf("DESCRIPTION:\n");
    printf("  Manage packages on github.\n");
    printf("\n");
    printf("USAGE:\n");
    printf("  $ %s [option] <github/url>\n", SCRIPT_NAME);
    printf("\n");
    printf("%s\n", help_sort());
    printf("\n");
    printf("EXAMPLES:\n");
    printf("\n");
    printf("This software is licensed under a Clear BSD License.\n");
    printf("Copyright (c) 2019 WestleyR, All rights reserved.\n");
    printf("Source code: https://github.com/WestleyR/gpack\n");
    return;
}

void version_print() {
    printf("%s\n", GPACK_VERSION);
    return;
}

int main(int argc, char **argv) {
    SCRIPT_NAME = argv[0];

    if (argc <= 1) {
        help_menu();
        return(1);
    }

    int verbose_print = 0;
    int debug_print = 0;

    int opt = 0;

    static struct option long_options[] = {
        {"verbose", no_argument, 0, 'v'},
        {"debug", no_argument, 0, 'd'},
        {NULL, 0, 0, 0}
    };

//    while ((opt = getopt_long(argc, argv,"o:T:S:vVhdtsl", long_options, 0)) != -1) {
    while ((opt = getopt_long(argc, argv,":vdVh", long_options, 0)) != -1) {
        switch (opt) {
             case 'v':
                 verbose_print = 1;
                 break;
             case 'd':
                 debug_print = 1;
                 break;
             case 'V':
                 version_print();
                 return(0);
                 break;
             case 'h':
                 help_menu();
                 return(0);
                 break;

             default:
                 printf("\n%s\n\n", help_sort());
                 return(22);
        }
    }

    if (optind < argc) {
        for (int i = optind; i < argc; i++) {
            printf("EXTRA OPTIONS: %s\n", argv[i]);
        }
    } else {
        print_errorf("No arguments\n");
        return(123);
    }

    set_verbose(verbose_print);
    set_debug(debug_print);


    print_verbosef("Test verbose\n");
    print_debugf("Test debug\n");


    return(0);
}

//
// End main-gpack.c
//
