//
//  main-gpack.c
//  gpack - https://github.com/WestleyR/gpack
//
// Created by WestleyR on Jun 16, 2019
// Source code: https://github.com/WestleyR/gpack
//
// Copyright (c) 2019-2021 WestleyR. All rights reserved.
// This software is licensed under a BSD 3-Clause Clear License.
// Consult the LICENSE file that came with this software regarding
// your rights to distribute this software.
//

#include "main-gpack.h"

#define CATPATH_IMPLEMENTATION
#include "catpath.h"

#ifndef COMMIT_HASH
#define COMMIT_HASH "unknown"
#endif

#ifndef UNCOMMITED_CHANGES
#define UNCOMMITED_CHANGES "[unknown]"
#endif

void help_menu(const char* script_name) {
  printf("Copyright (c) 2019-2021 WestleyR. All rights reserved.\n");
  printf("This software is licensed under a BSD 3-Clause Clear License.\n");
  printf("Consult the LICENSE file that came with this software regarding\n");
  printf("your rights to distribute this software.\n");
  printf("\n");
  printf("Source code: https://github.com/WestleyR/gpack\n");
  printf("\n");
  printf("Description\n");
  printf("  Manage user (non-root) binary/script packages.\n");
  printf("\n");
  printf("Usage\n");
  printf("  $ %s [option] [command] <option> <user/package-name>\n", script_name);
  printf("\n");
  printf("Commands\n");
  printf("  install    install a package/library\n");
  printf("  update     update gpack and database\n");
  printf("  upgrade    upgrade installed packages\n");
  printf("  remove     remove a package\n");
  printf("  autoclean  removes old packages, and remove broken\n");
  printf("             links from ~/.local/bin, ~/.local/lib\n");
  printf("             and ~/.local/include.\n");
  printf("  list       list all installed packages\n");
  printf("  search     search string for a package description\n");
  printf("  config     show help on how to configure a URL for repos\n");
  printf("\n");
  printf("Options\n");
  printf("  -h, --help     print help menu\n");
  printf("  -v, --verbose  verbose output\n");
  printf("  -d, --debug    debug output\n");
  printf("  -C, --commit   print the github commit hash\n");
  printf("  -V, --version  print version\n");
  printf("\n");
  printf("Other options\n");
  printf("  -f, --force    dont ask, just do\n");
  printf("  -r, --overide  overide the existing package\n");
  printf("  -n, --dry-run  dont remove anything, just print\n");
  printf("\n");
  printf("Examples\n");
  printf("  %s install WestleyR/ssum\n", script_name);
  printf("  %s remove WestleyR/ssum\n", script_name);
  printf("  %s autoclean\n", script_name);
  printf("\n");

 return;
}

void version_print() {
  printf("%s\n", GPACK_VERSION);
  return;
}

void print_commit() {
  printf("%s %s\n", UNCOMMITED_CHANGES, COMMIT_HASH);
}

int main(int argc, char **argv) {
  if (argc <= 1) {
    help_menu(argv[0]);
    return(1);
  }

  bool verbose_print = false;
  bool debug_print = false;
  bool force_flag = false;
  bool overide_flag = false;
  bool dry_run_flag = false;

  int opt = 0;

  static struct option long_options[] = {
    {"help", no_argument, 0, 'h'},
    {"version", no_argument, 0, 'V'},
    {"force", no_argument, 0, 'f'},
    {"overide", no_argument, 0, 'r'},
    {"dry-run", no_argument, 0, 'n'},
    {"commit", no_argument, 0, 'C'},
    {"verbose", no_argument, 0, 'v'},
    {"debug", no_argument, 0, 'd'},
    {NULL, 0, 0, 0}
  };

  while ((opt = getopt_long(argc, argv, "nvdfrVCh", long_options, 0)) != -1) {
    switch (opt) {
      case 'h':
        help_menu(argv[0]);
        return(0);
        break;
      case 'v':
        verbose_print = true;
        break;
      case 'f':
        force_flag = true;
        break;
      case 'r':
        overide_flag = true;
        break;
      case 'n':
        dry_run_flag = true;
        break;
      case 'd':
        debug_print = true;
        break;
      case 'V':
        version_print();
        return 0;
        break;
      case 'C':
        print_commit();
        return 0;
        break;
      default:
        return 22;
    }
  }

  set_verbose(verbose_print);
  set_debug(debug_print);

  if (optind < argc) {
    // TODO: this cli parsing is a bit messy...
    for (int i = optind; i < argc; i++) {
      if (strcmp(argv[i], "install") == 0) {
        for (int n = 1; n <= argc-1; n++) {
          if (argc - optind == 1) {
            print_errorf("Nothing to install...\n");
            return(1);
          }
          if (argv[i+n] == NULL) break;
          printf("I: Installing: %s ...\n", argv[i+n]);
          //get_description_for_package(argv[i+n]);
          // TODO: Pass the currect options
          if (install_pkg(argv[i+n], overide_flag) != 0) {
            return(1);
          }
        }
        printf("I: Total installed files: %d\n", check_installed_pkg());
        return(0);
        break;
      } else if (strcmp(argv[i], "update") == 0) {
        print_debugf("I: Updating packages...\n");
        update_pkg();
        //printf("I: Total installed files: %d\n", check_installed_pkg());
        return(0);
        break;
      } else if (strcmp(argv[i], "upgrade") == 0) {
        upgrade_pkg();
        printf("I: Total installed files: %d\n", check_installed_pkg());
        return(0);
        break;
      } else if (strcmp(argv[i], "remove") == 0) {
        if (argc - optind <= 1) {
          print_errorf("Nothing to remove...\n");
          return(1);
        }
        if (!force_flag) {
          char cont;
          fprintf(stderr, "This will remove:");
          for (int i = optind+1; i < argc; i++) fprintf(stderr, " %s", argv[i]);
          fprintf(stderr, "\nAre you sure you want to continue? [N/y] ");
          scanf("%c", &cont);
          if (cont != 'y' && cont != 'Y') {
            fprintf(stderr, "Abouting\n");
            return(1);
          }
        }
        for (int n = 1; n < argc-1; n++) {
          if (argv[i+n] == NULL) break;
          printf("I: Removing: %s ...\n", argv[i+n]);
          remove_pkg(argv[i+n]);
        }
        return(0);
        break;
      } else if (strcmp(argv[i], "search") == 0) {
        if (argc - optind <= 1) {
          if (search_pkg("", 1) != 0) {
            fprintf(stderr, "Failed to search for packages\n");
            return(1);
          }
          return(0);
        }
        if (argc - optind > 2) {
          fprintf(stderr, "Invalid arguments\n");
          return(22);
        }
        print_debugf("Pattern: %s\n", argv[i+1]);
        if (search_pkg(argv[i+1], 1) != 0) {
          fprintf(stderr, "Failed to search for packages\n");
          return(1);
        }
        return(0);
        break;
      } else if (strcmp(argv[i], "list") == 0) {
        list_packages();
        return(0);
      } else if (strcmp(argv[i], "autoclean") == 0) {
        return helper_autoclean(dry_run_flag);
        break;
      } else if (strcmp(argv[i], "config") == 0) {
        return show_config_help();
        break;
      } else {
        print_errorf("Unknown command: %s\n", argv[i]);
        return(22);
      }
    }
  } else {
    print_errorf("No arguments\n");
    return(123);
  }

  return(0);
}

// vim: tabstop=2 shiftwidth=2 expandtab autoindent softtabstop=0
