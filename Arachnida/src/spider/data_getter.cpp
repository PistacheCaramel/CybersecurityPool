#include "spider.h"

uint	wc(char *in, size_t size, size_t nmemb, TidyBuffer *out) 
{
	uint r;

	r = size * nmemb;
	tidyBufAppend(out, in, r);
	return r;
}

int	get_data_from_url(const char *url, TidyDoc *tdoc, TidyBuffer *docbuf, TidyBuffer *tidy_errbuff, int *err)
{
	char curl_errbuf[CURL_ERROR_SIZE];

	
    // libcurl Initialize
    CURL* curl = curl_easy_init();
    if (!curl) {
        write(2, "Error initializing libcurl\n", strlen("Error initializing libcurl\n"));
        return (1);
    }

    // Set request
	curl_easy_setopt(curl, CURLOPT_URL, url);
	curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, curl_errbuf);
	curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 0L);
	curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, wc);
    // Set tidy with curl to save data
	*tdoc = tidyCreate();
	tidyOptSetBool(*tdoc, TidyForceOutput, yes); /* try harder */
	tidyOptSetInt(*tdoc, TidyWrapLen, 4096);
	tidySetErrorBuffer(*tdoc, tidy_errbuff);
	tidyBufInit(docbuf);

	curl_easy_setopt(curl, CURLOPT_WRITEDATA, docbuf);
    // Execute the request
    *err = (int)curl_easy_perform(curl);
    // Clean-up
    curl_easy_cleanup(curl);
    return (0);
}
