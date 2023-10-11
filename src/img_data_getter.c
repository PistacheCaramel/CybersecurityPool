#include "spider.h"

size_t WriteImageCallback(void* ptr, size_t size, size_t nmemb, void* userp) {
    size_t total_size = size * nmemb;
    FILE	*file = (FILE *)userp;

    fwrite(ptr, size, nmemb, file);
    return total_size;
}

const char	*set_img_name(const char *url)
{
	char	*ptr;
	
	ptr = strstr(url, "//");
	while (++ptr && strstr(ptr, "/"))
		ptr = strstr(ptr, "/");
	if (ptr)
		ptr++;
	return (ptr);
}

int		get_image_data_from_url(const char *url)
{
    printf("JE SUIS ICI\n");

    // Initialize libcurl
	CURL* curl = curl_easy_init();
	if (!curl) {
		return (1);
	}
    // Set request
	curl_easy_setopt(curl, CURLOPT_URL, url);
               // Create file
	 char *filename;
	 const char	*ptr;
	
	 ptr = set_img_name(url);
	 filename = calloc(1, strlen(ptr) + strlen("img/") + 1);
	 strcpy(filename, "img/");
	 strcat(filename, ptr);
	FILE	*fp = fopen(filename, "w+");
	if (fp)
	{
    		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteImageCallback);
    		curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);

    // Execute request
    		CURLcode res = curl_easy_perform(curl);   
	// Error Check
    		if (res != CURLE_OK) {
			printf("img getting error\n");
    		} else {
    		}


		fclose(fp);
	}
	else
	{
		perror(filename);
	}
	free(filename);
     // Clean up
    curl_easy_cleanup(curl);

    // Close file
	return (0);
}
