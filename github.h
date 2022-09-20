#ifndef GITHUB_H
#define GITHUB_H

#include <string>
#include <vector>
#include <curl/curl.h>
#include <cjson/cJSON.h>

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
         * @brief Will retrieve the commits of a given repository by name
         * 
         * @param repo The name of the repository
         * @return std::vector<Commit> A vector of Commit objects of the given repository
         */
        std::vector<Commit> fetchCommits(std::string repo);

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
        
    public:
        /**
         * @brief Construct a new Github object
         * 
         * @param organization The name of the organization
         */
        Github(std::string organization);

        /**
         * @brief Fetch a specific project by assignment name
         * 
         * @param assignment The name of the assignment
         * @return std::vector<Repo> A vector of the repositories matching the name
         */
        std::vector<Repo> fetchProject(std::string assignment);

        /**
         * @brief Fetches all repositories in the organization
         * 
         * @return std::vector<Repo> A vector of all repositories in the organization
         */
        std::vector<Repo> fetchAllRepos();
    
};

#endif