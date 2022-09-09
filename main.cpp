#include "talcutil.h"

int main(int argc, char **argv) {
    struct commandArgs args;
    processArgs(&args, &argc, &argv);
    cJSON *json = cJSON_Parse(fetchRepos(args.organization).c_str());
        

    
    return 0;
}