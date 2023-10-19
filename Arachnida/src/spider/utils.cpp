#include "spider.h"

int	check_urls(std::string url)
{
	std::vector<std::string>::iterator	it;

	it = urls.begin();
	while (it != urls.end() && (*it).compare(url))
		it++;
	if (it == urls.end())
	{
		urls.push_back(url);
		return (1);
	}
	return (0);
}

int	handle_img_url(std::string url)
{
	std::vector<std::string>::iterator	it;

	it = imgs.begin();
	while (it != imgs.end() && (*it).compare(url))
		it++;
	if (it == imgs.end())
	{
		imgs.push_back(url);
		return (1);
	}
	return (0);
}
