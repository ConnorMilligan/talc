#include "repo.h"

Repo::Repo(cJSON *json) {
    this->name = cJSON_GetObjectItemCaseSensitive(json, "name")->valuestring;
}

std::string Repo::getName() {
    return this->name;
}

void Repo::setName(std::string name) {
    this->name = name;
}