#ifndef REPO_H
#define REPO_H

#include <iostream>
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

        /**
         * @brief A vector that contains the index of all commits with mismatched dates in the commit vector
         */
        std::vector<int> faultyCommits;
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

        /**
         * @brief Parse through the commits and add any that do not match to the according vector
         * 
         * @return bool if the repository has a faulty commit
         */
        bool findMismatchedDates();

        /**
         * @brief Prints out the repository information and the suspect commits
         */
        void printRepo();
};

#endif