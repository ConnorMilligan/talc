#include "commit.h"

#include <iostream>

Commit::Commit(cJSON *json) {
    // Fetch the author commit date as a string
    this->authorDate = cJSON_GetObjectItemCaseSensitive(
        cJSON_GetObjectItemCaseSensitive(
        cJSON_GetObjectItemCaseSensitive(
            json, "commit"), "author"), "date")->valuestring;

    // Fetch the commit date as a string
    this->commitDate = cJSON_GetObjectItemCaseSensitive(
        cJSON_GetObjectItemCaseSensitive(
        cJSON_GetObjectItemCaseSensitive(
            json, "commit"), "committer"), "date")->valuestring;

    // Fetch the commit message as a string
    this->commitMessage = cJSON_GetObjectItemCaseSensitive(
        cJSON_GetObjectItemCaseSensitive(
            json, "commit"), "message")->valuestring;
}

std::string Commit::getAuthorDate() {
    return this->authorDate;
}

std::string Commit::getCommitDate() {
    return this->commitDate;
}

std::string Commit::getCommitMessage() {
    return this->commitMessage;
}
