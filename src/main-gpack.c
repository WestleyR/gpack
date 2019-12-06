// Created by: WestleyR
// email: westleyr@nym.hush.com
// Date: Dec 1, 2019
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
#include "list.h"
#include "autoclean.h"
#include "update-pkg.h"
#include "upgrade-pkg.h"
#include "remove-pkg.h"

#include "logger/logger.h"

#ifndef COMMIT_HASH
#define COMMIT_HASH "unknown"
#endif

void help_menu(const char* script_name) {
  printf("DESCRIPTION:\n");
  printf("  Manage packages on github.\n");
  printf("\n");
  printf("USAGE:\n");
  printf("  $ %s [option] [command] <github/url>\n", script_name);
  printf("\n");
  printf("Commands:\n");
  printf("  install    install a package/library\n");
  printf("  update     update gpack and libraries\n");
  printf("  upgrade    upgrade installed packages\n");
  printf("             note: if a package version is 'master',\n");
  printf("             it will alwasy be reinstalled.\n");
  printf("  remove     remove a package\n");
  printf("  autoclean  remove broken links from ~/.gpack/bin,\n");
  printf("             ~/.local/lib and ~/.local/include.\n");
  printf("  list       list all installed packages\n");
  printf("\n");
  printf("OPTIONS:\n");
  printf("  -h, --help     print help menu\n");
  printf("  -v, --verbose  verbose output\n");
  printf("  -d, --debug    debug output\n");
  printf("  -C, --commit   print the github commit hash\n");
  printf("  -V, --version  print version\n");
  printf("\n");
  printf("EXAMPLES:\n");
  printf("  %s install WestleyR/ssum\n", script_name);
  printf("  %s remove WestleyR/ssum\n", script_name);
  printf("  %s autoclean\n", script_name);
  printf("\n");
  printf("Copyright (c) 2019 WestleyR, All rights reserved.\n");
  printf("This software is licensed under a Clear BSD License.\n");
  printf("Source code: https://github.com/WestleyR/gpack\n");
  return;
}

void version_print() {
  printf("%s\n", GPACK_VERSION);
  return;
}

void print_commit() {
  printf("%s\n", COMMIT_HASH);
}

int main(int argc, char **argv) {
  if (argc <= 1) {
    help_menu(argv[0]);
    return(1);
  }

  int verbose_print = 0;
  int debug_print = 0;

  int opt = 0;

  static struct option long_options[] = {
    {"help", no_argument, 0, 'h'},
    {"verbose", no_argument, 0, 'V'},
    {"commit", no_argument, 0, 'C'},
    {"verbose", no_argument, 0, 'v'},
    {"debug", no_argument, 0, 'd'},
    {NULL, 0, 0, 0}
  };

  //    while ((opt = getopt_long(argc, argv,"o:T:S:vVhdtsl", long_options, 0)) != -1) {
  while ((opt = getopt_long(argc, argv, "vdVCh", long_options, 0)) != -1) {
    switch (opt) {
      case 'h':
        help_menu(argv[0]);
        return(0);
        break;
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
      case 'C':
        print_commit();
        return(0);
        break;
      default:
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
          if (install_pkg(argv[i+n], 1) != 0) {
            return(1);
          }
        }
        return(0);
        break;
      } else if (strcmp(argv[i], "update") == 0) {
        printf("I: Updating packages...\n");
        update_pkg();
        return(0);
        break;
      } else if (strcmp(argv[i], "upgrade") == 0) {
        upgrade_pkg();
        return(0);
        break;
      } else if (strcmp(argv[i], "remove") == 0) {
        for (int n = 1; n < argc-1; n++) {
          if (argc - optind <= 0) {
            print_errorf("Nothing to remove...\n");
            return(1);
          }
          if (argv[i+n] == NULL) break;
          printf("I: Removing: %s ...\n", argv[i+n]);
          remove_pkg(argv[i+n]);
        }
        return(0);
        break;
      } else if (strcmp(argv[i], "list") == 0) {
        list_packages();
        return(0);
      } else if (strcmp(argv[i], "autoclean") == 0) {
        if (autoclean() != 0) {
          return(1);
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

// vim: tabstop=2 shiftwidth=2 expandtab autoindent softtabstop=0
