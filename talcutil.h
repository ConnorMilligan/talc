#ifndef TALCUTIL_H
#define TALCUTIL_H

#include <string>

/**
 * @brief Command line argument structure
 */
struct commandArgs {
    char *organization;
};

/**
 * @brief Will parse through the command line arguments
 * 
 * @param args A struct to store the parsed arguments in
 * @param argc 
 * @param argv 
 * @return int return code
 */
int processArgs(commandArgs *args, int *argc, char ***argv);

#endif