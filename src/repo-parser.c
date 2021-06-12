//
//  repo-parser.c for gpack
//  https://github.com/WestleyR/gpack
//
// Created by WestleyR on 2021-06-09
// Source code: https://github.com/WestleyR/gpack
//
// Copyright (c) 2021 WestleyR. All rights reserved.
// This software is licensed under a BSD 3-Clause Clear License.
// Consult the LICENSE file that came with this software regarding
// your rights to distribute this software.
//

#include "repo-parser.h"


// NEW FUNCS!!!

// The repo index is cached in ~/.cache/wst.gpack/repo-index.ini

char* download_repo_index(bool update) {
  char* repo_file = get_repo_index_file();

  if ((access(repo_file, F_OK) != 0) || update) {
    // Download the file since it does not exist
    printf("I: Downloading new repolist...\n");
    
    char* url = get_repolist_url();

    char* wget_cmd = (char*) malloc(512);
    wget_cmd[0] = '\0';
    sprintf(wget_cmd, "wget -q -O %s %s", repo_file, url);

    print_debugf("wget command: %s\n", wget_cmd);
    if (system(wget_cmd) != 0) {
      print_errorf("wget command failed\n");
      return NULL;
    }
    free(wget_cmd);
  }

  return repo_file;
}


// END NEW FUNCS!!!

repolist* new_repolist() {
  repolist* rp;
  rp = (repolist*) malloc(sizeof(repolist));
  rp->repo_count = 0;

  rp->repos = (repo**) malloc(sizeof(repo*) * 20); // max len of 20 for now...

  return rp;
}

int repolist_destroy(repolist* rp) {

  return 0;
}


ini_t* read_ini_file(const char* path) {
	FILE* fp = fopen(path, "r");
	fseek(fp, 0, SEEK_END);
	int size = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	char* data = (char*) malloc(size + 1);
	fread(data, 1, size, fp);
	data[size] = '\0';
	fclose(fp);

	ini_t* ini = ini_load(data, NULL);
	free(data);

  return ini;
}

repolist* parse_repofile(const char* filepath) {
  repolist* rl = new_repolist();

  ini_t* ini = read_ini_file(filepath);

  int count = ini_section_count(ini);
  printf("Looking though %d packages...\n", count);

  for (int i = 1; i < count; i++) {
    rl->repos[rl->repo_count] = (repo*) malloc(sizeof(repo));
    rl->repos[rl->repo_count]->name = strdup(
      ini_section_name(ini, i)
    );

    // Get the values from the ini file into the struct
    int dindex = ini_find_property(ini, i, "description", -1);
    rl->repos[rl->repo_count]->description = cpstr(
	    ini_property_value(ini, i, dindex)
    );

    dindex = ini_find_property(ini, i, "homepage", -1);
    rl->repos[rl->repo_count]->homepage = cpstr(
	    ini_property_value(ini, i, dindex)
    );

    char* arch = get_gpack_arch();
    dindex = ini_find_property(ini, i, arch, -1);
    rl->repos[rl->repo_count]->download_url = cpstr(
	    ini_property_value(ini, i, dindex)
    );

    dindex = ini_find_property(ini, i, "bin_files", -1);
    rl->repos[rl->repo_count]->bin_files = (char*) malloc(400);
    strcpy(rl->repos[rl->repo_count]->bin_files, "hello");
    rl->repos[rl->repo_count]->bin_files = cpstr(
	    ini_property_value(ini, i, dindex)
    );

    char* sha = get_binary_sha(arch);
    //free(arch); // TODO: not returning a malloced pointer (may need to...)
    dindex = ini_find_property(ini, i, sha, -1);
    rl->repos[rl->repo_count]->sha1 = cpstr(
	    ini_property_value(ini, i, dindex)
    );

    dindex = ini_find_property(ini, i, "version", -1);
    rl->repos[rl->repo_count]->version = cpstr(
	    ini_property_value(ini, i, dindex)
    );


    rl->repo_count++;
  }


//	ini_destroy(ini);

  return rl;
}

repo* get_obj_for_pkg(repolist* rl, const char* pkg) {
  for (int i = 0; i < rl->repo_count; i++) {
    if (strcmp(rl->repos[i]->name, pkg) == 0) {
      return rl->repos[i];
    }
  }

  return NULL;
}


// vim: tabstop=2 shiftwidth=2 expandtab autoindent softtabstop=0
