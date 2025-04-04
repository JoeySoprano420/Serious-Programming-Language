#include "distributed_linker.h"
#include <curl/curl.h>
#include <iostream>

void DistributedLinker::linkToCloudService(const std::string &serviceURL, const std::string &sourceCode) {
    CURL *curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, serviceURL.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, sourceCode.c_str());

        CURLcode res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            std::cerr << "Failed to link to cloud: " << curl_easy_strerror(res) << std::endl;
        }

        curl_easy_cleanup(curl);
    }
}
