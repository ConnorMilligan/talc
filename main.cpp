#include "talcutil.h"

#include <iostream>
#include <cjson/cJSON.h>

int main(int argc, char **argv) {
    struct commandArgs args;
    processArgs(&args, &argc, &argv);
    cJSON *json = cJSON_Parse(fetchRepos(args.organization).c_str());
    //std::cout << cJSON_Print(cJSON_GetArrayItem(json,29)) << std::endl;
    std::cout << cJSON_GetArraySize(json) << std::endl;
    
    return 0;
}