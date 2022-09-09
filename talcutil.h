#ifndef TALCUTIL_H
#define TALCUTIL_H

#include <iostream>

#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <curl/curl.h>
#include <cjson/cJSON.h>

struct commandArgs {
    char *organization;
};

struct memory {
   char *response;
   size_t size;
 };

int processArgs(commandArgs *args, int *argc, char ***argv);

std::string fetchRepos(std::string org);


#endif