#ifndef GITHUB_H
#define GITHUB_H

#include <string>
#include <vector>
#include <curl/curl.h>
#include <cjson/cJSON.h>

#include "repo.h"

#define NUM_PER_PAGE 100

class Github
{
private:
    std::string organization;
    int numRepos;

    int fetchNumRepos(std::string org);
    std::vector<Commit> fetchCommits(std::string repo);
    std::string fetchRepoPage(int page);
public:
    Github(std::string organization);

    std::vector<Repo> fetchProject(std::string assignment);
    std::vector<Repo> fetchAllRepos();


    
};

#endif