#include "argParser.h"
#include "github.h"
#include "bar.h"

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cjson/cJSON.h>
#include <ctime>

std::time_t getEpochTime(const std::string dateTime);
std::vector<std::string> readProfanityList(const std::string &filename);

int main(int argc, char **argv) {
    float progress;
    std::vector<int> falseRepos, lateRepos, profaneRepos;
    std::vector<std::string> profanity;
    std::time_t deadline;
    argParser args(argc, argv);

    if (args.getHelp()) {
        std::cout << "usage: talc [OPTIONS]" << std::endl << std::endl;
        std::cout << "Options:" << std::endl;
        std::cout << std::left << std::setw(30) << "\t-o, --organization STRING" << "The name of the organization." << std::endl;
        std::cout << std::left << std::setw(30) << "\t-p, --project STRING" << "A filter for which repositories to pull." << std::endl;
        std::cout << std::left << std::setw(30) << "\t-t, --time STRING" << "(Optional) Will flag repositories past this date" << std::endl;
        std::cout << std::left << std::setw(30) << "\t" << "Time is in UTC, i.e. 2022-09-18T19:59:00Z" << std::endl;

        return 0;
    }
    else if (getenv("GITHUB_TOKEN") == NULL) {
        std::cout << "No github token found. Make sure the \"GITHUB_TOKEN\" has been set!" << std::endl;
        return 1;
    }
    else if (args.getOrganization() == "") {
        std::cout << "Please use the -o flag to specify which organization you wish to pull repos from" << std::endl;
        return 1;
    }
    else if (args.getProject() == "") {
        std::cout << "Please use the -p flag to specify which project you would like to process" << std::endl;
        return 1;
    }

    profanity = readProfanityList("data/profanity.txt");

    if (profanity.size() == 0) {
        std::cout << "Ensure that the profanity file is accessible (./data/profanity.txt)." << std::endl;
        return 1;
    }

    // This isn't very readable, sorry
    Github github = (!args.getTime().empty()) ? Github(args.getOrganization(), args.getTime()) : Github(args.getOrganization());
    
    std::vector<Repo> repositories = github.fetchProject(args.getProject());

    // Make sure the next text doesn't overlap with the progress bar
    std::cout << std::endl;

    if (repositories.size() == 0) {
        std::cout << "No repositories with the project name found. Check for typos?" << std::endl;
        return 1;
    }

    std::cout << "Found " + std::to_string(repositories.size()) + " repositories that match the given project name!" << std::endl;

    std::cout << std::endl << "Fetching all commits for the pulled repositories..." << std::endl;
    github.setAllCommits(&repositories);
    
    std::cout << std::endl << "Searching repositories for suspect commits..." << std::endl;
    
    for (int i = 0; i < repositories.size(); i++) {
        if (!args.getTime().empty())
            repositories[i].findLateCommits(github.getDeadlineTime());
        
        if (repositories[i].findMismatchedDates()) 
            falseRepos.push_back(i);

        if (repositories[i].findProfaneCommits(profanity))
            profaneRepos.push_back(i);
    }

    std::cout << std::endl << "Found " + std::to_string(falseRepos.size()) + " repositories with mismatched commit times." << std::endl;

    for (int i = 0; i < falseRepos.size(); i++)
        repositories[falseRepos[i]].printMismatchRepo();

    std::cout << std::endl << "Found " + std::to_string(profaneRepos.size()) + " repositories with potentially profane content." << std::endl;

    for (int i = 0; i < profaneRepos.size(); i++)
        repositories[profaneRepos[i]].printProfaneRepo();
    
    std::cout << std::endl << std::endl << "Repositories with late commits:" << std::endl;

    for (int i = 0; i < falseRepos.size(); i++)
        if(repositories[i].isLate())
            std::cout << repositories[i].getName() << std::endl;

    
    return 0;
}

std::vector<std::string> readProfanityList(const std::string &filename) {
    std::vector<std::string> profanityList;
    std::ifstream file(filename);
    if (file.is_open()) {
        std::string word;
        while (getline(file, word)) {
            profanityList.push_back(word);
        }
        file.close();
    } else {
        std::cout << "Error: Unable to open profanity file." << std::endl;
    }
    return profanityList;
}