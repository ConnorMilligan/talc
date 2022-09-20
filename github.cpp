#include "github.h"

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

std::vector<Commit> Github::fetchCommits(std::string repo) {
    CURL *curl;
    CURLcode res;
    std::string readBuffer;
    std::string token = getenv("GITHUB_TOKEN");
    struct curl_slist *headers = NULL;
    std::vector<Commit> commits;

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

    for (int i = 0; i < cJSON_GetArraySize(cJSON_Parse(readBuffer.c_str())); i++) {
        Commit commit(cJSON_GetArrayItem(cJSON_Parse(readBuffer.c_str()),i));
        commits.push_back(commit);
    }

    return commits;
}

std::string Github::fetchRepoPage(int page) {
    CURL *curl;
    CURLcode res;
    cJSON *commits;
    std::string readBuffer, url;
    std::string token = getenv("GITHUB_TOKEN");
    struct curl_slist *headers = NULL;


    curl = curl_easy_init();
        
    if(curl) {
        url = "https://api.github.com/orgs/" + this->organization + "/repos?page=" + std::to_string(page);

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        printf("%s\n", url.c_str());
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
    std::vector<Repo> repositories;
    std::string repoString;
    int count = 1;

    do {
        repoString = fetchRepoPage(count);
        for (int i = 0; i < cJSON_GetArraySize(cJSON_Parse(repoString.c_str())); i++) {
            Repo myRepo(cJSON_GetArrayItem(cJSON_Parse(repoString.c_str()),i));
            printf("%d: %s\n", i+((count-1)*30), myRepo.getName().c_str());
            repositories.push_back(myRepo);
        }
        count++;
    } while (count < 2);


    printf("%d", repositories.size());

    return repositories;
}