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
    void setName(std::string name);
    
};

#endif