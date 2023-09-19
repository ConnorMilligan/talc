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

        /**
         * @brief A vector that contains the index of all commits with with text that trip the profanity filter
         */
        std::vector<int> profaneCommits;

        /**
         * @brief If the repository has commits past the deadline
         */
        bool pastDeadline;
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
         * @brief Parse through the commits and add any that trip the profanity filter to the according vector
         * 
         * @param profanityList list of profane words to compare against
         * 
         * @return bool if the repository has a potentially profane commit
         */
        bool findProfaneCommits(const std::vector<std::string> &profanityList);

        /**
         * @brief Flag the repository if there is a commit is passed the deadline
         * 
         * @param deadline the deadline of the project
         */
        void findLateCommits(std::string deadline);

        /**
         * @brief Checks if the repository is late
         * 
         * @return bool if the repo is late
         */
        bool isLate();

        /**
         * @brief Prints out the repository information and the mismatched commits
         */
        void printMismatchRepo();

        /**
         * @brief Prints out the repository information and the profane commits
         */
        void printProfaneRepo();
};

#endif