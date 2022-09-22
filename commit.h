#ifndef COMMIT_H
#define COMMIT_H

#include <string>
#include <cjson/cJSON.h>

class Commit {
    private:
        /**
         * @brief The author date
         */
        std::string authorDate;

        /**
         * @brief The commit date
         */
        std::string commitDate;

        /**
         * @brief The commit message
         */
        std::string commitMessage;
    public:
        /**
         * @brief Construct a new Commit object
         * 
         * @param json The commit in cJSON format
         */
        Commit(cJSON *json);

        /**
         * @brief Get the author date
         * 
         * @return std::string The author date
         */
        std::string getAuthorDate();

        /**
         * @brief Get the commit date
         * 
         * @return std::string The commit date
         */
        std::string getCommitDate();

        /**
         * @brief Get the commit message
         * 
         * @return std::string The commit message
         */
        std::string getCommitMessage();
};

#endif