#include "spider.h"

std::vector<std::string> urls;
std::vector<std::string> imgs;
int			levl;
int   link_handler(const char *url, int lvl)
{
	TidyDoc		tdoc;
	TidyBuffer	docbuf = {0};
	TidyBuffer	tidy_errbuf = {0};
	int 		err;

	if (lvl >= levl)
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
				std::cout << "------END OF REQUEST------" << std::endl;
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

int	check_extension(std::string to_check)
{
	std::string sub;
	
	sub = to_check.substr(to_check.size() - 5, 5);
	if (sub.compare(".jpeg") == 0)
		return (1);
	sub.erase(0, 1);
	if (sub.compare(".jpg") == 0 || sub.compare(".png") == 0
			|| sub.compare(".gif") == 0
			|| sub.compare(".bmp") == 0)
		return (1);
	return (0);
}

int	img_request(const char *path)
{
   	std::vector<std::string>::iterator img;
	
	img = imgs.begin();
	while (img != imgs.end())
	{
		if (check_extension(*img))
		{
			if (get_image_data_from_url((*img).c_str(), path))
				return (1);
		}
		img++;
	}
	return (0);
}

void	recursive_option(std::string::iterator *it, std::string **input)
{			
	levl = 5;
	*it += 2;
	if (*it + 1  != (*input)->end() 
			&& *(*it + 1) == '-' && *it + 2 != (*input)->end()
			&& *(*it + 2) == 'l' && *it + 3 != (*input)->end()
			&& *(*it + 3) == ' ' && *it + 4 != (*input)->end()
			&& isdigit(*(*it + 4)))
	{
		*it += 4;
		levl = 0;
		while (*it != (*input)->end() && isdigit(**it))
		{
			std::cout << "HERE" << std::endl;
			int	power = 0;
			levl = levl * pow(10, power)  + (**it) - 48;
			power++;
			(*it)++;
		}
	}

}
void	options_handler(std::string *input, std::string *path)
{
	std::string::iterator	it;
	it = input->begin();
	while (it != input->end() && *it == '-')
	{
		if (*(it + 1) == 'r' && *(it + 2) == ' ')
		{
			recursive_option(&it, &input);	
		}
		else if (it + 1 != input->end() && *(it + 1) == 'p'
				&& it + 2 != input->end())
		{
			size_t	pos;
			it += 3;
			pos = std::distance(input->begin(), it);
			while (it != input->end() && (*it) != ' ')
				it++;
			*path = input->substr(pos, std::distance(input->begin(), it) - pos).c_str();
		}
		else
			it++;
		while (it != input->end() && *it == ' ')
			it++;
		input->erase(input->begin(), it);
		it = input->begin();
	}
}

int main(int ac, char **av) {
	
	int		i;
	std::string	input;
	std::string	path;
	int		lvl = 0;

	path = "./data";
	levl = 1;
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
		if (av[i])
			input.append(" ");
	}
	int	ret;
	options_handler(&input, &path);
	if (input.empty() == false && (ret = link_handler(input.c_str(), lvl)) < 0)
		return (ret);
	if (img_request(path.c_str()))
		return (1);
    return (0);
}

