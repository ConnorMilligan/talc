#ifndef REPO_H
#define REPO_H

#include <string>
#include <vector>

#include "commit.h"

class Repo
{
private:
    std::string name;
    std::vector<Commit> commits;
public:
    Repo(std::string organization);

    
};

#endif