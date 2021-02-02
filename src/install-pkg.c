//
//  install-pkg.c
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

#include "install-pkg.h"

int link_files(const char* install_path, const char* binary_bin_files) {
  // Now link the installed files
  print_debugf("Looping to install files: %s\n", binary_bin_files);

  char* bin_files_dup = strdup(binary_bin_files);

  char* file_to_install;
  file_to_install = strtok(bin_files_dup, ",");
  while (file_to_install != NULL) {
    print_debugf("looped file: %s\n", file_to_install);

    char* source_bin_file = NULL;
    catpath(&source_bin_file, install_path);
    catpath(&source_bin_file, file_to_install);

    char* link_binfile = NULL;
    char* bin_dir = get_bin();
    catpath(&link_binfile, bin_dir);
    free(bin_dir);

    catpath(&link_binfile, basename(file_to_install));

    print_debugf("I: Linking: %s -> %s...\n", source_bin_file, link_binfile);

    // Check if the file exists before linking
    if (access(source_bin_file, F_OK) != 0) {
      // Source file does not exist
      print_errorf("Source file does not exist: %s please check the path is currect and fix it in your package file\n", source_bin_file);
      return -1;
    }

    if (symlink(source_bin_file, link_binfile) != 0) {
      print_errorf("Failed to link bin files\n");
      perror("symlink");
      return -1;
    }

    free(link_binfile);
    free(source_bin_file);
    file_to_install = strtok(NULL, ",");
  }

  free(bin_files_dup);

  return 0;
}

int install_pkg(const char* pkg, gpk_install_opts opts) {
  // TODO: Actrally use this!
  bool overide = false;

  if (opts != NULL) {
    for (int i = 0; i < GPK_INSTALL_MAX_OPTS; i++) {
      if (opts[i] == 0 || opts[i] == GPK_OPTS_END) break;
      if (opts[i] == GPK_INSTALL_OVERIDE) {
        print_debugf("Overidding install\n");
        overide = true;
      } else if (opts[i] == GPK_INSTALL_COMPILE_BUILD) {
        print_debugf("Compiling build\n");
      } else {
        fprintf(stderr, "%s(): WARNING: unknown option: %d\n", __func__, opts[i]);
      }
    }
  }

  char* pkg_file = pkg_file_registry_dir();

  // Panic check
  if (pkg_file == NULL) {
    print_errorf("Memmory alloc failed\n");
    // Exit the program ASAP since we are out of ram
    exit(1);
  }

  catpath(&pkg_file, pkg);

  print_debugf("package_file: %s\n", pkg_file);

  FILE* fp = fopen(pkg_file, "r");
  if (fp == NULL) {
    fprintf(stderr, "%s: package does not exist\n", pkg);
    free(pkg_file);
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
  const char* package_user_name = NULL;
  const char* package_version = NULL;
  const char* package_name = NULL;
  const char* package_build_command = NULL;

  if (strcmp(current_arch, "macos") == 0) {
    print_debugf("I: Downloading binary for macOS...\n");
    binary_url = get_macos_binary_url(ini);
    binary_ssum = get_macos_binary_ssum(ini);
    binary_bin_files = get_macos_binary_bin_files(ini);
  } else if (strcmp(current_arch, "x86_64_linux") == 0) {
    print_debugf("I: Downloading binary for x86_64_linux...\n");
    binary_url = get_x86_64_binary_url(ini);
    binary_ssum = get_x86_64_binary_ssum(ini);
    binary_bin_files = get_x86_64_binary_bin_files(ini);
  } else if (strcmp(current_arch, "armv6l") == 0) {
    print_debugf("I: Downloading binary for armv6l...\n");
    binary_url = get_armv6l_binary_url(ini);
    binary_ssum = get_armv6l_binary_ssum(ini);
    binary_bin_files = get_armv6l_binary_bin_files(ini);
  } else {
    print_errorf("Unknown arch for GPACK_ARCH: %s\n", current_arch);
    return -1;
  }
  // TODO: maybe need to free() these before re-defining it
  package_user_name = get_package_user_name(ini);
  package_version = get_package_version(ini);
  package_name = get_package_name(ini);

  int build_from_source = -1;
  if (binary_url == NULL) {
    print_debugf("I: No pre-compiled binary for your arch. Building from source...\n");
    build_from_source = 0;

    binary_url = get_package_build_url(ini);
    binary_ssum = get_package_build_ssum(ini);
    binary_bin_files = get_package_build_bin_files(ini);
    package_build_command = get_package_build_command(ini);

    print_debugf("BuildSource TURL: %s\n", binary_url);
    print_debugf("BuildSource SSUM: %s\n", binary_ssum);
    print_debugf("BuildSource BINS: %s\n", binary_bin_files);
    print_debugf("BuildSource BCMD: %s\n", package_build_command);

    print_debugf("Package Build command: %s\n", package_build_command);
  }

  print_debugf("UserName:       %s\n", package_user_name);
  print_debugf("Package:        %s\n", package_name);
  print_debugf("Version:        %s\n", package_version);
  print_debugf("Binary tarball: %s\n", binary_url);
  print_debugf("Tarball ssum:   %s\n", binary_ssum);
  print_debugf("BIN_FILES:      %s\n", binary_bin_files);

  // Make sure the package name is there
  if (package_name == NULL) {
    print_errorf("Package does not have a name: %s\n", pkg_file);
    return -1;
  }

  // Panic check
  if (binary_bin_files == NULL) {
    print_errorf("No binfiles to install.\n");
    return -1;
  }

  // Check if the package files are already installed
  { // New scope
    int files_installed = 0;
    int files_to_install = 0;

    char* bin_files_dup = strdup(binary_bin_files);

    char* file_to_install = strtok(bin_files_dup, ",");
    while (file_to_install != NULL) {
      print_debugf("looped file: %s\n", file_to_install);

      char* link_binfile = NULL;
      char* bin_dir = get_bin();
      catpath(&link_binfile, bin_dir);
      free(bin_dir);
      catpath(&link_binfile, basename(file_to_install));

      print_debugf("Checking if %s exists...\n", link_binfile);
      if (access(link_binfile, F_OK) == 0) {
        print_debugf("File %s already has the files installed\n", link_binfile);
        files_installed++;
      }
      free(link_binfile);

      file_to_install = strtok(NULL, ",");
      files_to_install++;
    }
    free(bin_files_dup);

    print_debugf("Files installed (by this package): %d\n", files_installed);
    print_debugf("Files to install: %d\n", files_to_install);

    if (files_to_install == files_installed) {
      print_errorf("Package %s is already installed.\n", pkg);

      // Cleanup
      // TODO: should have a cleanup function
      free(pkg_file);
      ini_destroy(ini);
      return -1;
    } else if (files_installed != 0) {
      print_errorf("Package %s is already installed.\n", pkg);
      print_warningf("Package %s has non-installed files. You may want to re-install this package.\n", pkg);

      // Cleanup
      // TODO: should have a cleanup function
      free(pkg_file);
      ini_destroy(ini);
      return -1;
    }
  }

  printf("I: Installing %s...\n", package_name);
  if (build_from_source == 0) {
    printf("I: No pre-compiled binary for your arch. Building from source...\n");
  } else {
    printf("I: Downloading binary for %s...\n", current_arch);
  }

  // Order of operation:
  //  1. Check if the package exists in cache
  //  2. Download the package if it does not exist
  //  3. Verify the checksum
  //  4. Untar and copy the files to the install dir
  //  5. Link the installed files to ~/.local/bin, ~/.local/include, etc...

  char* cache_path = get_cachepath_for_sha(binary_ssum);

  print_debugf("I: Cache path: %s\n", cache_path);

  if (does_cache_path_exist_and_ok(cache_path, binary_ssum) != 0) {
    print_debugf("I: Downloading since not cached...\n");

    // TODO: need better malloc len here
    char* wget_cmd = (char*) malloc(512);
    wget_cmd[0] = '\0';
    sprintf(wget_cmd, "wget -q --show-progress -O %s %s", cache_path, binary_url);

    print_debugf("wget command: %s\n", wget_cmd);
    if (system(wget_cmd) != 0) {
      print_errorf("wget command failed\n");
      return -1;
    }
    free(wget_cmd);
  }

  // Verify the tarball again
  if (does_cache_path_exist_and_ok(cache_path, binary_ssum) != 0) {
    print_warningf("Checksum missmatch. Did you enter the currect checksum in: %s?\n", pkg_file);
    // Continue even if checksum fails, since the package may be a "master" package and always
    // wants to be up-to-date.
  }

  // Now untar the tarball
  char* install_path = get_installdir_for_user_and_version(package_user_name, package_name, package_version);
  char tar_cmd[200];
  tar_cmd[0] = '\0';
  sprintf(tar_cmd, "tar -xf %s -C %s", cache_path, install_path);
  print_debugf("I: untar command: %s\n", tar_cmd);

  if (system(tar_cmd) != 0) {
    print_errorf("Failed to run untar cmd\n");
    return -1;
  }

  if (build_from_source == 0) {
    printf("I: Compiling source...\n");

    char compile_cmd[512];
    compile_cmd[0] = '\0';

    sprintf(compile_cmd, "cd %s && %s", install_path, package_build_command);

    printf("Build command: %s\n", compile_cmd);

    if (system(compile_cmd) != 0) {
      print_errorf("Failed to run build command: %s\n", compile_cmd);
      return -1;
    }
  }

  link_files(install_path, binary_bin_files);

  // Write the version so gpack can list it
  char* user_home_dir = getenv("HOME");

  char* package_version_file = NULL;
  catpath(&package_version_file, user_home_dir);
  catpath(&package_version_file, ".gpack/installed");
  catpath(&package_version_file, package_user_name);
  catpath(&package_version_file, package_name);
  catpath(&package_version_file, "version.gpack");

  print_debugf("package version file: %s\n", package_version_file);

  FILE* version_file = fopen(package_version_file, "w");
  if (version_file == NULL) {
    print_errorf("Failed to open version file: %s\n", package_version_file);
    return -1;
  }
  fprintf(version_file, "%s", package_version);

  fclose(version_file);

  free(install_path);
  free(pkg_file);
  free(package_version_file);
  free(cache_path);
  ini_destroy(ini);

  printf("I: Done installing %s\n", pkg);

  return(0);
}

// vim: tabstop=2 shiftwidth=2 expandtab autoindent softtabstop=0
