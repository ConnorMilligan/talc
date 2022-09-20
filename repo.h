#ifndef REPO_H
#define REPO_H

#include <string>
#include <vector>
#include <cjson/cJSON.h>

#include "commit.h"

/**
 * @brief Object representation of a repository
 */
class Repo {
    private:

        /**
         * @brief The name of the repository
         */
        std::string name;

        /**
         * @brief A vector containing all the commits in the repo
         */
        std::vector<Commit> commits;
    public:

        /**
         * @brief Construct a new Repo object
         * 
         * @param json The repository in cJSON format
         */
        Repo(cJSON *json);

        /**
         * @brief Get the name of the repository
         * 
         * @return std::string Name of the repository
         */
        std::string getName();

        /**
         * @brief Get the commits of the repository
         * 
         * @return std::vector<Commit> repo commits
         */
        std::vector<Commit> getCommits();

        /**
         * @brief Set the commit vector of the repository
         * 
         * @param commits vector of commits
         */
        void setCommits(std::vector<Commit> commits);
        
};

#endif