#include "talcutil.h"

int processArgs(commandArgs *args, int *argc, char ***argv) {
    args->aflag = 0;
    args->bflag = 0;
    args->cvalue = NULL;
    int c;

    printf("%d %d %s\n", args->aflag, args->bflag, args->cvalue);
    
    while ((c = getopt (*argc, *argv, "abc:")) != -1)
        switch (c) {
            case 'a':
            args->aflag = 1;
            break;
        case 'b':
            args->bflag = 1;
            break;
        case 'c':
            args->cvalue = optarg;
            break;
        case '?':
            if (optopt == 'c')
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