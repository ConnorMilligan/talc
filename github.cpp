#include "github.h"

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

std::string Github::getCommits(std::string repo) {
    CURL *curl;
    CURLcode res;
    std::string readBuffer;
    std::string token = getenv("GITHUB_TOKEN");
    struct curl_slist *headers = NULL;

    curl = curl_easy_init();

    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, ("https://api.github.com/repos/" + this->organization + '/'+ repo + "/commits").c_str());

        headers = curl_slist_append(headers, "User-Agent: Talc");
        headers = curl_slist_append(headers, ("Authorization: Bearer " + token).c_str());
        
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER,headers);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        res = curl_easy_perform(curl);
    
        curl_easy_cleanup(curl);
    }

    return readBuffer;
}


Github::Github() {
    this->organization = "";
}

Github::Github(std::string organization) {
    this->organization = organization;
}

std::vector<Repo> Github::fetchProject(std::string assignment) {
    std::vector<Repo> repositories;

    return repositories;
}

std::vector<Repo> Github::fetchAllRepos() {
    CURL *curl;
    CURLcode res;
    std::string readBuffer;
    std::string token = getenv("GITHUB_TOKEN");
    struct curl_slist *headers = NULL;
    std::vector<Repo> repositories;

    curl = curl_easy_init();

    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, ("https://api.github.com/orgs/" + this->organization + "/repos?page=2").c_str());

        headers = curl_slist_append(headers, "User-Agent: Talc");
        headers = curl_slist_append(headers, ("Authorization: Bearer " + token).c_str());
        
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER,headers);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        res = curl_easy_perform(curl);
    
        curl_easy_cleanup(curl);
    }

    Repo myRepo(cJSON_GetArrayItem(cJSON_Parse(readBuffer.c_str()),1));
    printf("%s\n",myRepo.getName().c_str());

    printf("%d\n",cJSON_GetArraySize(cJSON_Parse(getCommits(myRepo.getName()).c_str())));

    return repositories;
}