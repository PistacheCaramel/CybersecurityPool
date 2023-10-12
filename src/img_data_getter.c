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
	return (ptr);
}

int		get_image_data_from_url(const char *url)
{
	int	ret;

	ret = 0;

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
	 if (check_urls(ptr) == 0)
		return (0);
	 filename = calloc(1, strlen(ptr) + strlen("img/") + 1);
	 if (!filename)
		 return (1);
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
    		if (res != CURLE_OK) 
			write(2, "Request Error\n", strlen("Request Error\n"));
		fclose(fp);
	}
	else
	{
		ret = 1;
		perror(filename);
	}
	free(filename);
     // Clean up
    curl_easy_cleanup(curl);

    // Close file
	return (ret);
}
