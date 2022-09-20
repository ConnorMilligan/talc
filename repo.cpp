#include "repo.h"

Repo::Repo(cJSON *json) {
    //Fetches the name field from the JSON as a string
    this->name = cJSON_GetObjectItemCaseSensitive(json, "name")->valuestring;
    this->commits = std::vector<Commit>();
}

std::string Repo::getName() {
    return this->name;
}

std::vector<Commit> Repo::getCommits() {
    return this->commits;
}

void Repo::setCommits(std::vector<Commit> commits) {
    this->commits = commits;
}