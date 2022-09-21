#include "argParser.h"

#include <algorithm>

argParser::argParser(int argc, char **argv) {
    // Set the arguments to an empty string
    this->organization = "";
    this->project = "";

    // Add all the arguments to the vector
    for (int i=1; i < argc; ++i)
        this->arguments.push_back(std::string(argv[i]));

    std::vector<std::string>::const_iterator itr;

    // Parse the organization flag
    itr =  std::find(this->arguments.begin(), this->arguments.end(), "-o");

    if (itr != this->arguments.end() && ++itr != this->arguments.end())
        this->organization = *itr;

    // Parse the project flag
    itr =  std::find(this->arguments.begin(), this->arguments.end(), "-p");

    if (itr != this->arguments.end() && ++itr != this->arguments.end())
        this->project = *itr;

}

std::string argParser::getOrganization() {
    return this->organization;
}

std::string argParser::getProject() {
    return this->project;
}