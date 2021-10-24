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

// Order of operation:
//   download the repo index file if it does not exist (single file for all packages)
//   check if the package to install is in that list
//   check if the package has the correct arch in that list
//   download the package, and link the files

int link_files(cerror* err, const char* install_path, const char* binary_bin_files) {
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
      error_printf(err, "source file does not exist: %s please check the path is currect and fix it in your package file", source_bin_file);
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

int install_pkg(cerror* err, const char* pkg, bool force) {
  if (iserror(err)) {
    error_printf(err, "err already set");
    return -1;
  }

  // Make sure the repo-list is downloaded (and up-to-date (todo))
  char* repo_file = download_repo_index(false);
  if (repo_file == NULL) {
    return -1;
  }

  repolist* rl = parse_repofile(repo_file);

  repo* r = get_obj_for_pkg(rl, pkg);
  if (r == NULL) {
    error_printf(err, "package: %s does not exist", pkg);
    return -1;
  }

  printf("NAME         : %s\n", r->name);
  printf("DESCRIPTION  : %s\n", r->description);
  printf("DOWNLOAD_URL : %s\n", r->download_url);
  printf("BIN_FILES    : %s\n", r->bin_files);
  printf("VERSION      : %s\n", r->version);
  printf("SHA1         : %s\n", r->sha1);


  repolist_destroy(rl);
  free(repo_file);

//  // TODO: Actrally use this!
//  bool overide = false;

  { // New scope
    int files_installed = 0;
    int files_to_install = 0;

    char* bin_files_dup = strdup(r->bin_files);

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
      error_printf(err, "Package %s is already installed or you already installed this command name", pkg);

      // Cleanup
      // TODO: should have a cleanup function
      //free(pkg_file);
      //ini_destroy(ini);
      return -1;
    } else if (files_installed != 0) {
      print_errorf("Package %s is already installed.\n", pkg);
      print_warningf("Package %s has non-installed files. You may want to re-install this package.\n", pkg);

      // Cleanup
      // TODO: should have a cleanup function
      //free(pkg_file);
      //ini_destroy(ini);
      return -1;
    }
  }

  char* cache_path = get_cachepath_for_sha(r->sha1);

  printf("I: Cache path: %s\n", cache_path);
  print_debugf("I: Cache path: %s\n", cache_path);

  if (does_cache_path_exist_and_ok(cache_path, r->sha1) != 0) {
    print_debugf("I: Downloading since not cached...\n");

    // TODO: need better malloc len here
    char* wget_cmd = (char*) malloc(512);
    wget_cmd[0] = '\0';
    sprintf(wget_cmd, "wget -q --show-progress -O %s %s", cache_path, r->download_url);

    printf("wget command: %s\n", wget_cmd);
    print_debugf("wget command: %s\n", wget_cmd);
    if (system(wget_cmd) != 0) {
      print_errorf("wget command failed\n");
      return -1;
    }
    free(wget_cmd);
  }

  // Verify the tarball again
  if (does_cache_path_exist_and_ok(cache_path, r->sha1) != 0) {
    print_warningf("Checksum missmatch. Did you enter the currect checksum in: %s?\n", repo_file);
    // Continue even if checksum fails, since the package may be a "master" package and always
    // wants to be up-to-date.
  }

  // Now untar the tarball
  char* install_path = get_installdir_for_user_and_version(pkg, r->version);
  char tar_cmd[200];
  tar_cmd[0] = '\0';
  sprintf(tar_cmd, "tar -xf %s -C %s", cache_path, install_path);
  print_debugf("I: untar command: %s\n", tar_cmd);

  if (system(tar_cmd) != 0) {
    print_errorf("Failed to run untar cmd\n");
    return -1;
  }

  // Link the files
  link_files(err, install_path, r->bin_files);
  if (iserror(err)) {
    return -1;
  }

  // Write the version so gpack can list it
  char* user_home_dir = getenv("HOME");

  char* package_version_file = NULL;
  catpath(&package_version_file, user_home_dir);
  catpath(&package_version_file, ".gpack/installed");
  catpath(&package_version_file, pkg);
  catpath(&package_version_file, "version.gpack");

  print_debugf("package version file: %s\n", package_version_file);

  FILE* version_file = fopen(package_version_file, "w");
  if (version_file == NULL) {
    print_errorf("Failed to open version file: %s\n", package_version_file);
    return -1;
  }
  fprintf(version_file, "%s", r->version);

  fclose(version_file);

  free(install_path);
//  free(pkg_file);
  free(package_version_file);
  free(cache_path);
//  ini_destroy(ini);

  printf("I: Done installing %s\n", pkg);

  return(0);
}

// vim: tabstop=2 shiftwidth=2 expandtab autoindent softtabstop=0
