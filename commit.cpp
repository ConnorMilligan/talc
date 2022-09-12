#include "commit.h"

Commit::Commit(cJSON *json) {
    this->authorDate = cJSON_GetObjectItemCaseSensitive(
        cJSON_GetObjectItemCaseSensitive(
        cJSON_GetObjectItemCaseSensitive(
            json, "name"), "author"), "commit")->valuestring;

    this->commitDate = cJSON_GetObjectItemCaseSensitive(
        cJSON_GetObjectItemCaseSensitive(
        cJSON_GetObjectItemCaseSensitive(
            json, "name"), "committer"), "commit")->valuestring;
}

std::string Commit::getAuthorDate() {
    return this->authorDate;
}

std::string Commit::getCommitDate() {
    return this->commitDate;
}