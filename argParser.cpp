#include "argParser.h"

#include <algorithm>

argParser::argParser(int argc, char **argv) {
    // Set the arguments to an empty string
    this->organization = "";

    // Add all the arguments to the vector
    for (int i=1; i < argc; ++i)
        this->arguments.push_back(std::string(argv[i]));

    // Parse the organization flag
    std::vector<std::string>::const_iterator itr;
    itr =  std::find(this->arguments.begin(), this->arguments.end(), "-o");

    if (itr != this->arguments.end() && ++itr != this->arguments.end())
        this->organization = *itr;
}

std::string argParser::getOrganization() {
    return this->organization;
}