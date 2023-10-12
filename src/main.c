#include "spider.h"

char	**urls;

int   link_handler(const char *url, int lvl)
{
	TidyDoc		tdoc;
	TidyBuffer	docbuf = {0};
	TidyBuffer	tidy_errbuf = {0};
	int 		err;

	if (lvl > 1)
        	return (0); 
     // Data getter
	if (get_data_from_url(url, &tdoc, &docbuf, &tidy_errbuf, &err))
		err = 1;
	if(!err)
	{
		err = tidyParseBuffer(tdoc, &docbuf); /* parse the input */
		if(err >= 0)
		{
			err = tidyCleanAndRepair(tdoc); /* fix any problems */
			if(err >= 0)
			{
				err = tidyRunDiagnostics(tdoc); /* load tidy error buffer */
				printf("///////    STOOOOP ////\n");
				if(err >= 0)
				{
					err = html_data_parsing(tdoc, tidyGetRoot(tdoc), 0, lvl, url); /* walk the tree */
					//fprintf(stderr, "%s\n", tidy_errbuf.bp);  show errors 
				}
			}
		}
		tidyBufFree(&docbuf);
		tidyBufFree(&tidy_errbuf);
		tidyRelease(tdoc);
	}

    // Clean-up
    return err;

}

int main(int ac, char **av) {

   (void) ac;
	int	ret;
	urls = calloc(sizeof(char *), 400);
	if ((ret = link_handler(av[1], 0)) < 0)
	{
		free_urls();
		return (ret);
	}
    free_urls();
    return (0);
}

