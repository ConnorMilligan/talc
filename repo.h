#ifndef REPO_H
#define REPO_H

#include <string>
#include <vector>
#include <cjson/cJSON.h>

#include "commit.h"

class Repo
{
private:
    std::string name;
    std::vector<Commit> commits;
public:
    Repo(cJSON *json);

    std::string getName();
    std::vector<Commit> getCommits();

    void setCommits(std::vector<Commit> commits);
    
};

#endif