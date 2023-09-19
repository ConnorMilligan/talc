#include "repo.h"
#include "time.h"

#include <ctime>
#include <regex>

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


bool Repo::findProfaneCommits(const std::vector<std::string> &profanityList) {
    // build regex pattern
    std::string pattern = "\\b(";

    for (size_t i = 0; i < profanityList.size(); ++i) {
        pattern += (i > 0 ? "|" : "") + profanityList[i];
    }
    pattern += ")\\b";

    // case insensitive
    std::regex regexPattern(pattern, std::regex_constants::icase);

    for (int i = 0; i < this->commits.size(); i++) {
        std::string currMessage = this->commits[i].getCommitMessage();
        for (char &c : currMessage) {
            c = tolower(c);
        }
        for (const std::string& word : profanityList) {
            if (currMessage.find(word) != std::string::npos) {
                std::cout <<  currMessage + " " + word << std::endl;
                this->profaneCommits.push_back(i);
            }
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

void Repo::printMismatchRepo() {
    std::cout << "──────────────────────────────────────────────" << std::endl;
    std::cout << "Name: " + this->name << std::endl;
    std::cout << "Commits: " + std::to_string(this->commits.size()) << std::endl;
    std::cout << "Suspect commits: " + std::to_string(this->faultyCommits.size()) << std::endl;
    std::cout << std::endl << " ~<>~ Mismatched commits ~<>~" << std::endl;

    for (int i = 0; i < this->faultyCommits.size(); i++) {
        std::cout << "Commit #" << this->faultyCommits[i] << std::endl;
        std::cout << " * Commit message: " << this->commits[this->faultyCommits[i]].getCommitMessage() << std::endl;
        std::cout << " * Author date: " << this->commits[this->faultyCommits[i]].getAuthorDate() << std::endl;
        std::cout << " * Commit date: " << this->commits[this->faultyCommits[i]].getCommitDate() << std::endl<< std::endl;
    }
}

void Repo::printProfaneRepo() {
    std::cout << "──────────────────────────────────────────────" << std::endl;
    std::cout << "Name: " + this->name << std::endl;
    std::cout << "Commits: " + std::to_string(this->commits.size()) << std::endl;
    std::cout << "Suspect commits: " + std::to_string(this->profaneCommits.size()) << std::endl;
    std::cout << std::endl << " ~<>~ Profane commits ~<>~" << std::endl;

    for (int i = 0; i < this->profaneCommits.size(); i++) {
        std::cout << "Commit #" << this->profaneCommits[i] << std::endl;
        std::cout << " * Commit message: " << this->commits[this->profaneCommits[i]].getCommitMessage() << std::endl;
        std::cout << " * Commit date: " << this->commits[this->profaneCommits[i]].getCommitDate() << std::endl<< std::endl;
    }
}