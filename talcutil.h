#ifndef TALCUTIL_H
#define TALCUTIL_H

#include <string>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <curl/curl.h>

struct commandArgs
{
    char *organization;
};

int processArgs(commandArgs *args, int *argc, char ***argv);

int fetchRepos(std::string org);


#endif