#ifndef GITHUB_H
#define GITHUB_H

#include <string>
#include <vector>
#include <curl/curl.h>
#include <cjson/cJSON.h>
#include <ctime>


#include "repo.h"

/**
 * @brief Number of repos to fetch per each request (Max. 100)
 */
#define NUM_PER_PAGE 100

/**
 * @brief 
 */
class Github {
    private:
        /**
         * @brief Name of the organization
         */
        std::string organization;

        /**
         * @brief Number of repos in the repository
         */
        int numRepos;

        /**
         * @brief a vector of the repositories in the organization
         */
        std::vector<Repo> repositories;

        /**
         * @brief The deadline of the project
         */
        std::string deadline;

        /**
         * @brief Returns the number of repositories in the organization
         * 
         * This will fetch the number of repositories provided by the organization
         * as opposed to checking the number Repo objects.
         * 
         * @param org The name of the organization to fetch.
         * @return int The number of repositories
         */
        int fetchNumRepos(std::string org);

        /**
         * @brief Will retrieve the commits of a given repository
         * 
         * @param repo A pointer to the repo to add commits to
         */
        void fetchCommits(Repo *repo);

        /**
         * @brief Retrieves the REST API response for a given page
         * 
         * The github REST API cannot fetch all repositories at the same time,
         * it can only fetch up to NUM_PER_PAGE. This will fetch the output 
         * given the page.
         * 
         * @param page The page number
         * @return std::string The raw rest API output of the given page
         */
        std::string fetchRepoPage(int page);


        /**
         * @brief Fetches all repositories in the organization
         * 
         * @return std::vector<Repo> A vector of all repositories in the organization
         */
        std::vector<Repo> fetchAllRepos();


        /**
         * @brief Parses the string in a date format to a ctime object
         * 
         * https://stackoverflow.com/questions/4781852/how-to-convert-a-string-to-datetime-in-c
         * 
         * @param dateTime - The date as a string
         * @return std::time_t the date in ctime
         */
        std::time_t getEpochTime(const std::string dateTime);
        
    public:
        /**
         * @brief Construct a new Github object
         * 
         * @param organization The name of the organization
         */
        Github(std::string organization);

        /**
         * @brief Construct a new Github object
         * 
         * @param organization The name of the organization
         * @param deadline The deadline for the project
         */
        Github(std::string organization, std::string deadline);

        /**
         * @brief Fetch a specific project by assignment name
         * 
         * @param assignment The name of the assignment
         * @return std::vector<Repo> A vector of the repositories matching the name
         */
        std::vector<Repo> fetchProject(std::string assignment);

        /**
         * @brief Fetches and sets all the commits of all repositories in a vector
         * 
         * @param repositories Pointer to a vector of repositories
         */
        void setAllCommits(std::vector<Repo> *repositories);

        /**
         * @brief Get the Deadline Time as a string
         * 
         * @return std::string deadline in string format
         */
        std::string getDeadlineTime();
};

#endif