#ifndef ARG_PARSER_H
#define ARG_PARSER_H

#include <string>
#include <vector>

class argParser {
    private:
        /**
         * @brief The name of the organization
         */
        std::string organization;

        /**
         * @brief The project to fetch
         */
        std::string project;

        /**
         * @brief A vector of all the command line arguments passed
         */
        std::vector<std::string> arguments;
    public:
        /**
         * @brief Construct a new arg Parser
         * 
         * @param argc 
         * @param argv 
         */
        argParser(int argc, char **argv);

        /**
         * @brief Get the Organization
         * 
         * @return std::string 
         */
        std::string getOrganization();

        /**
         * @brief Get the Project
         * 
         * @return std::string 
         */
        std::string getProject();
};

#endif