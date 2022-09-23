#include "argParser.h"

#include <algorithm>

// This is really messy and i'll fix it (maybe)
argParser::argParser(int argc, char **argv) {
    // Set the arguments to an empty string
    this->organization = "";
    this->project = "";
    this->time = "";
    this->help = false;

    // Add all the arguments to the vector
    for (int i=1; i < argc; ++i)
        this->arguments.push_back(std::string(argv[i]));

    std::vector<std::string>::const_iterator itr;

    // Parse the organization flag
    itr =  std::find(this->arguments.begin(), this->arguments.end(), "-o");

    if (itr != this->arguments.end() && ++itr != this->arguments.end())
        this->organization = *itr;

    
    itr =  std::find(this->arguments.begin(), this->arguments.end(), "--organization");

    if (itr != this->arguments.end() && ++itr != this->arguments.end())
        this->organization = *itr;

    // Parse the project flag
    itr =  std::find(this->arguments.begin(), this->arguments.end(), "-p");

    if (itr != this->arguments.end() && ++itr != this->arguments.end())
        this->project = *itr;


    itr =  std::find(this->arguments.begin(), this->arguments.end(), "--project");

    if (itr != this->arguments.end() && ++itr != this->arguments.end())
        this->project = *itr;

    // Parse the time flag
    itr =  std::find(this->arguments.begin(), this->arguments.end(), "-t");

    if (itr != this->arguments.end() && ++itr != this->arguments.end())
        this->time = *itr;

    itr =  std::find(this->arguments.begin(), this->arguments.end(), "--time");

    if (itr != this->arguments.end() && ++itr != this->arguments.end())
        this->time = *itr;

    // Parse the help flag
    for (int i = 0; i < this->arguments.size(); i++)
        if (this->arguments[i] == "-h" || this->arguments[i] == "--help")
            this->help = true;
    

}

std::string argParser::getOrganization() {
    return this->organization;
}

std::string argParser::getProject() {
    return this->project;
}

std::string argParser::getTime() {
    return this->time;
}

bool argParser::getHelp() {
    return this->help;
}