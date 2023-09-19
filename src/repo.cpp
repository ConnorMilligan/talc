#include "repo.h"
#include "time.h"

#include <ctime>

Repo::Repo(cJSON *json) {
    //Fetches the name field from the JSON as a string
    this->name = cJSON_GetObjectItemCaseSensitive(json, "name")->valuestring;
    this->commits = std::vector<Commit>();
    this->faultyCommits = std::vector<int>();
    this->pastDeadline = false;
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


bool Repo::findMismatchedDates() {
    for (int i = 0; i < this->commits.size(); i++) {
        if (this->commits[i].getAuthorDate() != this->commits[i].getCommitDate()) {
            this->faultyCommits.push_back(i);
        }
    }
    return (this->faultyCommits.size() != 0);
}

void Repo::findLateCommits(std::string deadline) {
    time_t commitTime, deadlineTime = getEpochTime(deadline);

    for (int i = 0; i < this->commits.size(); i++) {
        commitTime = getEpochTime(this->commits[i].getCommitDate());
        if (std::difftime(commitTime, deadlineTime) >= 0.0f) {
            this->pastDeadline = true;
            // Sorry (but not actually)
            break;
        }
    }
}

bool Repo::isLate() {
    return this->pastDeadline;
}

// This is a bit sloppy, i'll change it to an overloaded operator later
void Repo::printRepo() {
    std::cout << "──────────────────────────────────────────────" << std::endl;
    std::cout << "Name: " + this->name << std::endl;
    std::cout << "Commits: " + std::to_string(this->commits.size()) << std::endl;
    std::cout << "Suspect commits: " + std::to_string(this->faultyCommits.size()) << std::endl;
    std::cout << std::endl << " ~<>~ Odd commits ~<>~" << std::endl;

    for (int i = 0; i < this->faultyCommits.size(); i++) {
        std::cout << "Commit #" << this->faultyCommits[i] << std::endl;
        std::cout << " * Commit message: " << this->commits[this->faultyCommits[i]].getCommitMessage() << std::endl;
        std::cout << " * Author date: " << this->commits[this->faultyCommits[i]].getAuthorDate() << std::endl;
        std::cout << " * Commit date: " << this->commits[this->faultyCommits[i]].getCommitDate() << std::endl<< std::endl;
    }
}