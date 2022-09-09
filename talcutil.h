#ifndef TALCUTIL_H
#define TALCUTIL_H

#include <string>

struct commandArgs {
    char *organization;
};

int processArgs(commandArgs *args, int *argc, char ***argv);

std::string fetchRepos(std::string org);


#endif