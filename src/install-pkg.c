// Created by: WestleyR
// Email: westleyr@nym.hush.com
// Url: https://github.com/WestleyR/gpack
// Last modified date: 2020-12-31
//
// This file is licensed under the terms of
//
// The Clear BSD License
//
// Copyright (c) 2019-2020 WestleyR
// All rights reserved.
//
// This software is licensed under a Clear BSD License.
//

#include "install-pkg.h"

char* replace_char(char* str, char find, char replace){
  char *current_pos = strchr(str,find);
  while (current_pos) {
    *current_pos = replace;
    current_pos = strchr(current_pos,find);
  }
  return str;
}

int open_package(const char* pkg, int overide, int compile_build) {
  char pkg_file[256];
  pkg_file[0] = '\0';

  char* h = getenv("HOME");
  if (h == NULL) {
    printf("HOME not set!???\n");
    return(1);
  }

  strcpy(pkg_file, h);
  strcat(pkg_file, "/.gpack/packages/");
  strcat(pkg_file, pkg);

  FILE* fp = fopen(pkg_file, "r");
  if (fp == NULL) {
    fprintf(stderr, "%s: package does not exist\n", pkg);
    return -1;
  }
  fclose(fp);


  char installed_pkg[256];
  installed_pkg[0] = '\0';

  strcpy(installed_pkg, h);
  strcat(installed_pkg, "/.gpack/installed/");
  strcat(installed_pkg, pkg);

  if (overide == 0) {
    struct stat sb;
    if (stat(installed_pkg, &sb) == 0 && S_ISDIR(sb.st_mode)) {
      printf("%s: is already installed\n", pkg);
      // TODO: this should not be 0
      return(0);
    }
  }

  char cmd[256];
  cmd[0] = '\0';

  char* installer_script = get_installer();

  if (compile_build == 1) {
    printf("I: Compiling from release\n");
    strcpy(cmd, "GPACK_COMPILE_BUILD=true ");
  }
  if (overide == 1) {
    print_debugf("Overidding install...\n");
    strcpy(cmd, "GPACK_OVERIDE=true ");
  }
  // TODO: when the logger package supports this function
  //if (debug_status() == 1) {
  //  strcpy(cmd, "GPACK_DEBUG=true ");
  //}
  strcat(cmd, installer_script);

  free(installer_script);

  strcat(cmd, pkg_file);

#ifdef DEBUG
  printf("Executing install script: %s\n", cmd);
#endif

  if (system(cmd) != 0) {
    fprintf(stderr, "Failed to install: %s\n", pkg);
    print_debugf("Removing package that failed to install...\n");
    remove_pkg(pkg);
    return(1);
  }

  return 0;
}

int install_pkg(const char* pkg, int check_installed, int compile_build, int overide) {
//  if (open_package(pkg, overide, compile_build) != 0) {
//    return(1);
//  }

  char pkg_file[256];
  pkg_file[0] = '\0';

  char* h = getenv("HOME");
  if (h == NULL) {
    printf("HOME not set!???\n");
    return(1);
  }

  strcpy(pkg_file, h);
  strcat(pkg_file, "/.gpack/packages/");
  strcat(pkg_file, pkg);

  print_debugf("package_file: %s\n", pkg_file);

  FILE* fp = fopen(pkg_file, "r");
  if (fp == NULL) {
    fprintf(stderr, "%s: package does not exist\n", pkg);
    return -1;
  }

  // Load the package file into memory
	fseek(fp, 0, SEEK_END);
	int size = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	char* data = (char*) malloc(size + 1);
	fread(data, 1, size, fp);
	data[size] = '\0';
	fclose(fp);

	ini_t* ini = ini_load(data, NULL);
	free(data);

  const char* current_arch = getenv("GPACK_ARCH");
  if (current_arch == NULL) {
    print_errorf("GPACK_ARCH not set. Please set to: macos, x86_64_linux, or armv6l\n");
    return -1;
  }

  const char* binary_url = NULL;
  const char* binary_ssum = NULL;
  const char* binary_bin_files = NULL;

  if (strcmp(current_arch, "macos") == 0) {
    printf("I: Downloading binary for macOS...\n");
    binary_url = get_macos_binary_url(ini);
    binary_ssum = get_macos_binary_ssum(ini);
    binary_bin_files = get_macos_binary_bin_files(ini);
  } else if (strcmp(current_arch, "x86_64_linux") == 0) {
    printf("I: Downloading binary for x86_64_linux...\n");
    binary_url = get_x86_64_binary_url(ini);
    binary_ssum = get_x86_64_binary_ssum(ini);
    binary_bin_files = get_x86_64_binary_bin_files(ini);
  } else if (strcmp(current_arch, "armv6l") == 0) {
    printf("I: Downloading binary for armv6l...\n");
    binary_url = get_armv6l_binary_url(ini);
    binary_ssum = get_armv6l_binary_ssum(ini);
    binary_bin_files = get_armv6l_binary_bin_files(ini);
  } else {
    print_errorf("Unknown arch for GPACK_ARCH: %s\n", current_arch);
    return -1;
  }

  printf("URL:       %s\n", binary_url);
  printf("SSUM:      %s\n", binary_ssum);
  printf("BIN_FILES: %s\n", binary_bin_files);

  // TODO: I want to free ini right after I'm done using it, but it also
  // destroys the binary_url, binary_ssum, etc...
	//ini_destroy(ini);

  // Order of operation:
  //  1. Check if the package exists in cache
  //  2. Download the package if it does not exist
  //  3. Verify the checksum
  //  4. Untar and copy the files to the install dir
  //  5. Link the installed files to ~/.local/bin, ~/.local/include, etc...

  char* cache_path = get_cachepath_for_sha(binary_ssum);

  printf("I: Cache path: %s\n", cache_path);

  if (does_cache_path_exist_and_ok(cache_path) != 0) {
    printf("I: Downloading since not cached...\n");

    char* wget_cmd = (char*) malloc(200);
    wget_cmd[0] = '\0';
    sprintf(wget_cmd, "wget -q --show-progress -O %s %s", cache_path, binary_url);

    printf("wget command: %s\n", wget_cmd);
  }




	ini_destroy(ini);
  free(cache_path);

  printf("I: Done installing %s\n", pkg);

  return(0);
}

// vim: tabstop=2 shiftwidth=2 expandtab autoindent softtabstop=0
