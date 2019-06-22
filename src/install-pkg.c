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

#include "install-pkg.h"
#include "config.h"

#include "logger/logger.h"

#define LOG ".gpack.log"

int exec_command(char* cmd) {
    return(system(cmd));
}

/*char* replace(char* str, char* a, char* b) {
    int len  = strlen(str);
    int lena = strlen(a), lenb = strlen(b);
    for (char* p = str; p = strstr(p, a); ++p) {
        if (lena != lenb) // shift end as needed
            memmove(p+lenb, p+lena, len - (p - str) + lenb);
        memcpy(p, b, lenb);
    }

    return str;
}*/

char* replace_char(char* str, char find, char replace){
    char *current_pos = strchr(str,find);
    while (current_pos) {
        *current_pos = replace;
        current_pos = strchr(current_pos,find);
    }
    return str;
}

int unzip_pkg(char* path, char* to) {
    printf("I: Unzipping: %s ...\n", path);
    char unzip_cmd[256] = "unzip -qq -d ";
    strcat(unzip_cmd, to);
    strcat(unzip_cmd, " ");
    strcat(unzip_cmd, path);
//    printf("UNZIP_CMD: %s\n", unzip_cmd);
    return(exec_command(unzip_cmd));
}

int if_pkg_file(const char* pkg) {
    int infile = 1; // 1 = no/fail, 0 = yes/success
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    FILE *fp = fopen("pkg.list", "r");

    if (!fp) {
        printf("E: Unable to open file: %s\n", strerror(errno));
        return(-1);
    }

    while ((read = getline(&line, &len, fp)) != -1) {
        line[strcspn(line, "\n")] = 0;
        if (!strcmp(line, pkg)) {
            infile = 0;
            break;
        }
    }
    fclose(fp);

    return(infile);
}

int add_pkg(const char* pkg) {

    int err = if_pkg_file(pkg);
    if (err == -1) {
        printf("E: PANIC\n");
        exit(1);
    } else if (err == 0) {
        printf("E: Pkg is already in file\n");
        return(0);
    }

    FILE *fp;
    fp = fopen("pkg.list", "a");
    if (fp == NULL) {
        print_errorf("Error opening file: %s\n", strerror(errno));
        return(1);
    }
    print_debugf("Adding: %s to pkg file...\n", pkg);
    fputs(pkg, fp);
    fputs("\n", fp);

// TODO: close the file when done

//    fclose(fp);

    return(0);
}

int build_pkg(char* path) {
    printf("I: Building package: %s ...\n", path);
    char make_cmd[256] = "make -C ";
    strcat(make_cmd, path);
    strcat(make_cmd, "/* ");
    strcat(make_cmd, ">> ");
    strcat(make_cmd, LOG);
    return(exec_command(make_cmd));
}

int install_pkg(const char* pkg) {
    char *pkg_name = replace_char(strdup(pkg), '/', '_');

    char *pkg_name_zip = strdup(pkg_name);

    strcat(pkg_name_zip, ".zip");
    print_debugf("REPO_NAME: %s\n", pkg_name);

    char wget_cmd[256] = "wget -qq -O ";
    strcat(wget_cmd, pkg_name_zip);

    char url[256] = " https://";

    strcat(url, pkg);

    print_debugf("URL: %s\n", url);

    int err = if_pkg_file(url);
    if (err == -1) {
        printf("E: PANIC\n");
        exit(1);
    } else if (err == 0) {
        printf("E: Pkg is already installed\n");
        return(0);
    }

    strcat(wget_cmd, url);

    strcat(wget_cmd, "/archive/master.zip");

    print_debugf("URL: %s\n", wget_cmd);

    if (exec_command(wget_cmd) != 0) {
        print_errorf("ERROR CODE: %i: %s\n", errno, strerror(errno));
    }

    print_debugf("ZIP_NAME: %s\n", pkg_name_zip);
//    if (unzip_pkg(pkg_name_zip, pkg_name) != 0) {
    if (unzip_pkg(pkg_name_zip, REPO_DIR) != 0) {
        print_errorf("ERROR CODE: %i: %s\n", errno, strerror(errno));
    }

//    printf("YYYYYYYYYYYYYYY\n");

    print_debugf("Building package: %s ...\n", pkg_name);
//    char dir[100];
//    sprintf(dir, "%s/%s", REPO_DIR, pkg_name);
    if (build_pkg(REPO_DIR) != 0) {
        print_errorf("BUILD FAILED: nil\n");
    }

    print_debugf("Writing to file...\n");
    if (add_pkg(url) != 0) {
        print_errorf("failed writing pkg file: %s\n", strerror(errno));
    }

    url[0] = '\0';
    pkg_name[0] = '\0';
    pkg_name_zip[0] = '\0';

    return(0);
}

//
// End install-pkg.c
//
