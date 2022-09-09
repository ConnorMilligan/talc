#ifndef TALCUTIL_H
#define TALCUTIL_H

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

struct commandArgs
{
    int aflag, bflag;
    char *cvalue;
};

int processArgs(commandArgs *args, int *argc, char ***argv);



#endif