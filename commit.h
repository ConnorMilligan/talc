#ifndef COMMIT_H
#define COMMIT_H

#include <string>
#include <cjson/cJSON.h>

class Commit
{
private:
    std::string authorDate;
    std::string commitDate;
public:
    Commit(cJSON *json);

    std::string getAuthorDate();
    std::string getCommitDate();
};

#endif