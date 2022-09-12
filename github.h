#ifndef GITHUB_H
#define GITHUB_H

#include <string>
#include <vector>
#include <curl/curl.h>
#include <cjson/cJSON.h>

#include "repo.h"

class Github
{
private:
    std::string organization;
public:
    Github();
    Github(std::string organization);

    std::vector<Repo> fetchProject(std::string assignment);
    std::vector<Repo> fetchAllRepos();


    
};

#endif