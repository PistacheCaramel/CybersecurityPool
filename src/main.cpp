#include "spider.h"

std::vector<std::string> urls;
std::vector<std::string> imgs;

int   link_handler(const char *url, int lvl)
{
	TidyDoc		tdoc;
	TidyBuffer	docbuf = {0};
	TidyBuffer	tidy_errbuf = {0};
	int 		err;

	if (lvl > 7)
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

int	img_request(const char *path)
{
   	std::vector<std::string>::iterator img;
	
	img = imgs.begin();
	while (img != imgs.end())
	{
		if (get_image_data_from_url((*img).c_str(), path))
			return (1);
		img++;

	}
	return (0);
}

int main(int ac, char **av) {
	
	int		i;
	std::string	input;
	std::string	path;
	int		lvl = 2;

	path = "./data";
	if (ac < 2)
	{
		std::cout << "Should at least take 1 argument" << std::endl;
		return (0);
	}
	i = 1;
	while (av[i])
	{
		input.append(av[i]);
		i++;
	}
	int	ret;
	if ((ret = link_handler(input.c_str(), lvl)) < 0)
		return (ret);
	if (img_request(path.c_str()))
		return (1);
    return (0);
}

