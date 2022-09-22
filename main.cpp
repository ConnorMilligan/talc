#include "argParser.h"
#include "github.h"

#include <iostream>
#include <cjson/cJSON.h>

int main(int argc, char **argv) {
    argParser args(argc, argv);

    if (args.getOrganization() == "") {
        std::cout << "Please use the -o flag to specify which organization you wish to pull repos from" << std::endl;
        return 0;
    }
    else if (args.getProject() == "") {
        std::cout << "Please use the -p flag to specify which project you would like to process" << std::endl;
        return 0;
    }


    Github github(args.getOrganization());
    std::vector<Repo> repositories = github.fetchProject(args.getProject());

    // Make sure the next text doesn't overlap with the progress bar
    std::cout << std::endl;

    if (repositories.size() == 0) {
        std::cout << "No repositories with the project name found. Check for typos?" << std::endl;
        return 0;
    }

    std::cout << "Found " + std::to_string(repositories.size()) + " repositories that match the given project name!" << std::endl;

    //cJSON *json = cJSON_Parse(fetchRepos(args.organization).c_str());
    //std::cout << cJSON_Print(cJSON_GetArrayItem(json,29)) << std::endl;
    //std::cout << cJSON_GetArraySize(json) << std::endl;
    
    return 0;
}