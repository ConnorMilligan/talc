#include "talcutil.h"

int processArgs(commandArgs *args, int *argc, char ***argv) {
    args->organization = "\0";
    int c;
    
    while ((c = getopt (*argc, *argv, "o:")) != -1)
        switch (c) {
        case 'o':
            args->organization = optarg;
            break;
        case '?':
            if (optopt == 'o')
                fprintf (stderr, "Option -%c requires an argument.\n", optopt);
            else if (isprint (optopt))
                fprintf (stderr, "Unknown option `-%c'.\n", optopt);
            else
                fprintf (stderr,
                    "Unknown option character `\\x%x'.\n",
                    optopt);
            return 0;
        default:
            abort ();
    }
}

int fetchRepos(std::string org) {
    CURL *curl;
    CURLcode res;

    curl = curl_easy_init();
    std::string token = getenv("GITHUB_TOKEN");
    struct curl_slist *headers = NULL;

    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, ("https://api.github.com/orgs/" + org + "/repos").c_str());
        headers = curl_slist_append(headers, "User-Agent: Talc");
        headers = curl_slist_append(headers, ("Authorization: Bearer " + token).c_str());
        
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER,headers);

        res = curl_easy_perform(curl);

        if(res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
                curl_easy_strerror(res));
            return 1;
        }
    
        curl_easy_cleanup(curl);
    }
    return 0;
}