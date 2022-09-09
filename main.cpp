#include <iostream>
#include "talcutil.h"

int main(int argc, char **argv) {
    

    struct commandArgs args;
    processArgs(&args, &argc, &argv);
    if (fetchRepos(args.organization) != 0);
        std::cout << "Failed to fetch the organization." << std::endl;

    
    return 0;
}