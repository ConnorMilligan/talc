#include "github.h"
#include "bar.h"

#include <stdexcept>
#include <sstream>
#include <iomanip>

// This is the writer to put the output of the API call to a string
// it's magic. don't touch it.
static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

Github::Github(std::string organization) {
    this->organization = organization;
    this->numRepos = fetchNumRepos(organization);
    this->repositories = fetchAllRepos();
    this->deadline = "";
}

Github::Github(std::string organization, std::string deadline) {
    this->deadline = deadline;
    std::cout << "Entered time for deadline in local timezone: " << this->getDeadlineTime() << std::endl;

    this->organization = organization;
    this->numRepos = fetchNumRepos(organization);
    this->repositories = fetchAllRepos();
}

int Github::fetchNumRepos(std::string org) {
    CURL *curl;
    CURLcode res;
    std::string readBuffer;
    std::string token = getenv("GITHUB_TOKEN");
    struct curl_slist *headers = NULL;
    cJSON *organization;

    // Preform the curl
    curl = curl_easy_init();

    if(curl) {
        // Fetch the organization
        curl_easy_setopt(curl, CURLOPT_URL, ("https://api.github.com/orgs/" + org).c_str());

        // Set the user agent and authentication in the header
        headers = curl_slist_append(headers, "User-Agent: Talc");
        headers = curl_slist_append(headers, ("Authorization: Bearer " + token).c_str());
        
        // Apply the headers to the call
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER,headers);
        // Set the write function to use (to write the CURL output to a variable)
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        // Set the variable to output to
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        // Preform the curl!
        res = curl_easy_perform(curl);
    
        // Always clean up!
        curl_easy_cleanup(curl);
    }

    // Parse the raw string into a cJSON
    organization = cJSON_Parse(readBuffer.c_str());

    // Prevent a segfault by giving a readable error;
    // This is an awful way to handle this error... too bad!
    if (!cJSON_HasObjectItem(organization, "total_private_repos"))
        throw std::invalid_argument("The given organization cannot be found!");

    // Return the total repos field as a string
    return cJSON_GetObjectItemCaseSensitive(organization, "total_private_repos")->valueint;
}


void Github::fetchCommits(Repo *repo) {
    CURL *curl;
    CURLcode res;
    std::string readBuffer;
    std::string token = getenv("GITHUB_TOKEN");
    struct curl_slist *headers = NULL;
    std::vector<Commit> commits;

    // Initialize the CURL
    curl = curl_easy_init();

    if(curl) {
        // Fetch the commits of a repo
        curl_easy_setopt(curl, CURLOPT_URL, ("https://api.github.com/repos/" + this->organization + '/'+ repo->getName() + "/commits").c_str());

        // Set the user agent and authentication in the header
        headers = curl_slist_append(headers, "User-Agent: Talc");
        headers = curl_slist_append(headers, ("Authorization: Bearer " + token).c_str());
        
        // Apply the headers to the call
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER,headers);
        // Set the write function to use (to write the CURL output to a variable)
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        // Set the variable to output to
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        // Preform the curl!
        res = curl_easy_perform(curl);
    
        // Always clean up!
        curl_easy_cleanup(curl);
    }

    // The output is essentially an array of JSONs, this will loop through said array
    // and, build the commit object based on the data and push it to the commit vector
    for (int i = 0; i < cJSON_GetArraySize(cJSON_Parse(readBuffer.c_str())); i++) {
        Commit commit(cJSON_GetArrayItem(cJSON_Parse(readBuffer.c_str()),i));
        commits.push_back(commit);
    }
    repo->setCommits(commits);
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
        // Fetches a page of the organization repos
        url = "https://api.github.com/orgs/" + this->organization + "/repos?page=" + std::to_string(page) + "&per_page=" + std::to_string(NUM_PER_PAGE);
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());


        // Set the user agent and authentication in the header
        headers = curl_slist_append(headers, "User-Agent: Talc");
        headers = curl_slist_append(headers, ("Authorization: Bearer " + token).c_str());
        
        // Apply the headers to the call
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER,headers);
        // Set the write function to use (to write the CURL output to a variable)
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        // Set the variable to output to
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        // Preform the curl!
        res = curl_easy_perform(curl);
    
        // Always clean up!
        curl_easy_cleanup(curl);
    }

        
    return readBuffer;
}

std::vector<Repo> Github::fetchProject(std::string assignment) {
    std::vector<Repo> projectRepos;    
    
    for (int i = 0; i < this->repositories.size(); i++) {
        if (this->repositories[i].getName().find(assignment) != std::string::npos) {
            projectRepos.push_back(this->repositories[i]);
        }
    }

    return projectRepos;
}

std::vector<Repo> Github::fetchAllRepos() {
    std::vector<Repo> repositories;
    cJSON *repoPage;
    float progress;
    int count = 1;

    printf("Fetching repositories from %s...\n", this->organization.c_str());

    // Loop until the fetched page has less than the set page number
    // TODO: will crash if the divisor is 0, this can be fixed by changing NUM_PER_PAGE
    do {
        //Print a progress bar
        progress = float(repositories.size())/float(this->numRepos);
        print_progressbar(progress,"Progress: ", (std::to_string(int(progress*100)) + "%").c_str());

        repoPage = cJSON_Parse(fetchRepoPage(count).c_str());
        // Build the fetched repos into objects and add to the vector
        for (int i = 0; i < cJSON_GetArraySize(repoPage); i++) {
            Repo myRepo(cJSON_GetArrayItem(repoPage,i));
            //printf("%d: %s\n", i+((count-1)*NUM_PER_PAGE), myRepo.getName().c_str());
            repositories.push_back(myRepo);
        }
        
        count++;

    } while (cJSON_GetArraySize(repoPage) == NUM_PER_PAGE);;

    // Make sure it prints out 100% at the end.
    progress = float(repositories.size())/float(this->numRepos);
    print_progressbar(progress,"Progress: ", (std::to_string(int(progress*100)) + "%").c_str());

    return repositories;
}

void Github::setAllCommits(std::vector<Repo> *repositories) {
    float progress;

    for (int i = 0; i < repositories->size(); i++) {
        progress = float(i)/float(repositories->size());
        print_progressbar(progress,"Progress: ", (std::to_string(int(progress*100)) + "%").c_str());

        fetchCommits(&repositories->at(i));
    }

    print_progressbar(1,"Progress: ", "100%");

}

std::time_t Github::getEpochTime(const std::string dateTime) {
   static const std::string dateTimeFormat{ "%Y-%m-%dT%H:%M:%SZ" };
   std::istringstream ss{ dateTime };
   std::tm dt;

   ss >> std::get_time(&dt, dateTimeFormat.c_str());
   return std::mktime(&dt);
}

std::string Github::getDeadlineTime() {
    time_t deadline = this->getEpochTime(this->deadline);
    return asctime(gmtime(&deadline));
}