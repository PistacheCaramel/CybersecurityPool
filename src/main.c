#include "spider.h"

int   link_handler(const char *url, int lvl)
{
	TidyDoc		tdoc;
	TidyBuffer	docbuf = {0};
	TidyBuffer	tidy_errbuf = {0};
	int 		err;

	if (lvl > 2)
        	return (0); 
     // Data getter
	get_data_from_url(url, &tdoc, &docbuf, &tidy_errbuf, &err);
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
					html_data_parsing(tdoc, tidyGetRoot(tdoc), 0, lvl, url); /* walk the tree */
					//fprintf(stderr, "%s\n", tidy_errbuf.bp);  show errors 
				}
			}
		}
		tidyBufFree(&docbuf);
		tidyBufFree(&tidy_errbuf);
		tidyRelease(tdoc);
	}
    else
      printf("error\n");

    // Clean-up
    return err;

}

int main(int ac, char **av) {

   (void) ac;
	int	ret;
    if ((ret = link_handler(av[1], 0)) < 0)
	    return (ret);
    return (0);
}

