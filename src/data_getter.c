#include "spider.h"

size_t writeCallback(void *rec, size_t size, size_t nmemb, void *userdata) {
    size_t total_size = size * nmemb;
    struct s_data	*data;

    data = (struct s_data *)userdata;
    char *ptr = (char*)realloc(data->data, data->size + total_size + 1);
    if(ptr == NULL)
    return 0;  /* out of memory! */

  data->data = ptr;
  memcpy(&(data->data[data->size]), rec, total_size);
  data->size += total_size;
  data->data[data->size] = 0;
    return total_size;
}

struct s_data	get_data_from_url(const char *url)
{
	struct s_data  response;

    response.data = NULL;
    response.size = 0;
	
    // libcurl Initialize
	printf("Url:%s\n", url);
    CURL* curl = curl_easy_init();
    if (!curl) {
        printf("Erreur lors de l'initialisation de libcurl\n");
        return (response);
    }

    // Set request
    curl_easy_setopt(curl, CURLOPT_URL, url);

    // Save the data in a string
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    // Execute the request
    CURLcode res = curl_easy_perform(curl);
    // Error check
    if (res != CURLE_OK) {
        printf("Erreur lors de la requête : %s\n", curl_easy_strerror(res));
    	curl_easy_cleanup(curl);
    }
    curl_easy_cleanup(curl);
    return (response);
}

