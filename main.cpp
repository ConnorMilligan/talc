#include <iostream>
#include <curl/curl.h>

using namespace std;

int main() {
    CURL *curl;
    CURLcode res;

    curl = curl_easy_init();
    string token = getenv("GITHUB_TOKEN");
    struct curl_slist *headers = NULL;

    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "https://api.github.com/octocat");
        headers = curl_slist_append(headers, "User-Agent: Talc");
        headers = curl_slist_append(headers, ("Authorization: Bearer " + token).c_str());
        
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER,headers);

        res = curl_easy_perform(curl);

        if(res != CURLE_OK)
        fprintf(stderr, "curl_easy_perform() failed: %s\n",
                curl_easy_strerror(res));
    
        curl_easy_cleanup(curl);
    }
    return 0;
}