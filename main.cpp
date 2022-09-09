#include <iostream>
#include <curl/curl.h>
#include "talcutil.h"

using namespace std;

int main(int argc, char **argv) {
    CURL *curl;
    CURLcode res;

    struct commandArgs args;
    processArgs(&args, &argc, &argv);

    printf ("aflag = %d, bflag = %d, cvalue = %s\n",
          args.aflag, args.bflag, args.cvalue);

    for (int index = optind; index < argc; index++)
        printf ("Non-option argument %s\n", argv[index]);
    return 0;


    curl = curl_easy_init();
    string token = getenv("GITHUB_TOKEN");
    struct curl_slist *headers = NULL;

    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "https://api.github.com/orgs/uvmcs120s202");
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