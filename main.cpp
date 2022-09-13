#include "talcutil.h"
#include "github.h"

#include <iostream>
#include <cjson/cJSON.h>

int main(int argc, char **argv) {
    struct commandArgs args;
    
    
    processArgs(&args, &argc, &argv);
    
    Github github(args.organization);
    std::vector<Repo> repositories = github.fetchAllRepos();

    std::cout << repositories[0].getCommits()[0].getAuthorDate() << std::endl;

    //cJSON *json = cJSON_Parse(fetchRepos(args.organization).c_str());
    //std::cout << cJSON_Print(cJSON_GetArrayItem(json,29)) << std::endl;
    //std::cout << cJSON_GetArraySize(json) << std::endl;
    
    return 0;
}