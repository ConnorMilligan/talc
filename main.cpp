#include "argParser.h"
#include "github.h"
#include "bar.h"

#include <ctime>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cjson/cJSON.h>

std::time_t getEpochTime(const std::wstring& dateTime);

int main(int argc, char **argv) {
    float progress;
    std::vector<int> falseRepos, lateRepos;
    argParser args(argc, argv);

    if (args.getHelp()) {
        std::cout << "Help me!!" << std::endl;
        return 0;
    }
    else if (args.getOrganization() == "") {
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

    std::cout << std::endl << "Fetching all commits for the pulled repositories..." << std::endl;
    github.setAllCommits(&repositories);
    
    std::cout << std::endl << "Searching repositories for faulty commits..." << std::endl;
    
    for (int i = 0; i < repositories.size(); i++)
        if (repositories[i].findMismatchedDates()) 
            falseRepos.push_back(i);

    std::cout << std::endl << "Found " + std::to_string(falseRepos.size()) + " repositories with mismatched commit times." << std::endl;

    for (int i = 0; i < falseRepos.size(); i++)
        repositories[falseRepos[i]].printRepo();
    
    
    
    return 0;
}


// https://stackoverflow.com/questions/4781852/how-to-convert-a-string-to-datetime-in-c
std::time_t getEpochTime(const std::wstring& dateTime) {
   static const std::wstring dateTimeFormat{ L"%Y-%m-%dT%H:%M:%SZ" };
   std::wistringstream ss{ dateTime };
   std::tm dt;

   ss >> std::get_time(&dt, dateTimeFormat.c_str());
   return std::mktime(&dt);
}