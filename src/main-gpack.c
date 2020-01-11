// Created by: WestleyR
// email: westleyr@nym.hush.com
// Date: Dec 25, 2019
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
#include "search.h"
#include "utils.h"

#include "logger/logger.h"

#ifndef COMMIT_HASH
#define COMMIT_HASH "unknown"
#endif

void help_menu(const char* script_name) {
  printf("Description\n");
  printf("  Manage packages on github.\n");
  printf("\n");
  printf("Usage\n");
  printf("  $ %s [option] [command] <option> <github/url>\n", script_name);
  printf("\n");
  printf("Commands\n");
  printf("  install    install a package/library\n");
  printf("  update     update gpack and libraries\n");
  printf("  upgrade    upgrade installed packages\n");
  printf("  remove     remove a package\n");
  printf("  autoclean  remove broken links from ~/.gpack/bin,\n");
  printf("             ~/.local/lib and ~/.local/include.\n");
  printf("  list       list all installed packages\n");
  printf("  search     search string for a package description\n");
  printf("\n");
  printf("Options\n");
  printf("  -h, --help     print help menu\n");
  printf("  -v, --verbose  verbose output\n");
  printf("  -d, --debug    debug output\n");
  printf("  -C, --commit   print the github commit hash\n");
  printf("  -V, --version  print version\n");
  printf("\n");
  printf("Other options\n");
  printf("  -c, --compile  only compile the package, dont use\n");
  printf("                 the pre-compiled binaries\n");
  printf("  -f, --force    dont ask, just do\n");
  printf("  -r, --overide  overide the existing package\n");
  printf("  -n, --dry-run  dont remove anything, just print\n");
  printf("\n");
  printf("Examples\n");
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

int helper_autoclean(int dry_run) {
  // For ~/.gpack/bin
  char* bin_dir = get_bin();
  if (bin_dir == NULL) {
    fprintf(stderr, "Failed to get gpack bin dir\n");
    return(1);
  }
  print_debugf("Cleaning bin dir: %s\n", bin_dir);
  if (autoclean(bin_dir, dry_run) != 0) {
    return(1);
  }
  free(bin_dir);

  // For ~/.local/lib
  char* lib_dir = get_lib_dir();
  if (lib_dir == NULL) {
    fprintf(stderr, "Failed to get gpack bin dir\n");
    return(1);
  }
  print_debugf("Cleaning lib dir: %s\n", lib_dir);
  if (autoclean(lib_dir, dry_run) != 0) {
    return(1);
  }
  free(lib_dir);

  // For ~/.local/include
  char* include_dir = get_include_dir();
  if (include_dir == NULL) {
    fprintf(stderr, "Failed to get gpack bin dir\n");
    return(1);
  }
  print_debugf("Cleaning include dir: %s\n", include_dir);
  if (autoclean(include_dir, dry_run) != 0) {
    return(1);
  }
  free(include_dir);

  return(0);
}

int main(int argc, char **argv) {
  if (argc <= 1) {
    help_menu(argv[0]);
    return(1);
  }

  int verbose_print = 0;
  int debug_print = 0;
  int compile_build = 0;
  int force_flag = 0;
  int overide_flag = 0;
  int dry_run_flag = 0;

  int opt = 0;

  static struct option long_options[] = {
    {"help", no_argument, 0, 'h'},
    {"version", no_argument, 0, 'V'},
    {"compile", no_argument, 0, 'c'},
    {"force", no_argument, 0, 'f'},
    {"overide", no_argument, 0, 'r'},
    {"dry-run", no_argument, 0, 'n'},
    {"commit", no_argument, 0, 'C'},
    {"verbose", no_argument, 0, 'v'},
    {"debug", no_argument, 0, 'd'},
    {NULL, 0, 0, 0}
  };

  while ((opt = getopt_long(argc, argv, "nvdfrVcCh", long_options, 0)) != -1) {
    switch (opt) {
      case 'h':
        help_menu(argv[0]);
        return(0);
        break;
      case 'v':
        verbose_print = 1;
        break;
      case 'c':
        compile_build = 1;
        break;
      case 'f':
        force_flag = 1;
        break;
      case 'r':
        overide_flag = 1;
        break;
      case 'n':
        dry_run_flag = 1;
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
          if (install_pkg(argv[i+n], 1, compile_build, overide_flag) != 0) {
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
        upgrade_pkg(compile_build);
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
        int ret_code = helper_autoclean(dry_run_flag);
        return(ret_code);
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
