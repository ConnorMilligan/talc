#include "talcutil.h"

#include <unistd.h>


int processArgs(commandArgs *args, int *argc, char ***argv) {
    args->organization = "\0";
    int c;
    
    while ((c = getopt (*argc, *argv, "o:")) != -1)
        switch (c) {
        case 'o':
            args->organization = optarg;
            break;
        case '?':
            if (optopt == 'o')
                fprintf (stderr, "Option -%c requires an argument.\n", optopt);
            else if (isprint (optopt))
                fprintf (stderr, "Unknown option `-%c'.\n", optopt);
            else
                fprintf (stderr,
                    "Unknown option character `\\x%x'.\n",
                    optopt);
            return 0;
        default:
            abort ();
    }
}
