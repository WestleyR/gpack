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
#include "install-pkg.h"
#include "update-pkg.h"
#include "remove-pkg.h"

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
    while ((opt = getopt_long(argc, argv,"vdVh:", long_options, 0)) != -1) {
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

    set_verbose(verbose_print);
    set_debug(debug_print);

    if (optind < argc) {
        for (int i = optind; i < argc; i++) {
            if (strcmp(argv[i], "install") == 0) {
                for (int n = 1; n <= argc-1; n++) {
                    if (argc - optind == 1) {
                        print_errorf("Nothing to install...\n");
                        return(1);
                    }
                    if (argv[i+n] == NULL) break;
                    printf("I: Installing: %s ...\n", argv[i+n]);
                    install_pkg(argv[i+n]);
                }
                return(0);
                break;
            } else if (strcmp(argv[i], "update") == 0) {
                printf("I: Updating packages...\n");
                update_pkg();
                return(0);
                break;
            } else if (strcmp(argv[i], "remove") == 0) {
                for (int n = 1; n < argc-1; n++) {
                    if (argc <= 3) {
                        print_errorf("Nothing to remove...\n");
                        return(1);
                    }
                    if (argv[i+n] == NULL) break;
                    printf("I: Removing: %s ...\n", argv[i+n]);
                    remove_pkg(argv[i+n]);
                }
                return(0);
                break;
            } else {
                print_errorf("Unknown command: %s\n", argv[i]);
                return(1);
            }
        }
    } else {
        print_errorf("No arguments\n");
        return(123);
    }

    return(0);
}

//
// End main-gpack.c
//
