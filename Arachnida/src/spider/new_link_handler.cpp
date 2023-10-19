#include "spider.h"

int	new_link(int lvl, const char *url, TidyAttr href)
{
	const char	*link_name;
	char	*newlink;
	const char	*domain_name;

	link_name = tidyAttrValue(href);
	if (strncmp(link_name, "https://", 8) == 0)
	{
			if (check_urls(link_name))
				return (link_handler(link_name, lvl + 1));
	}
	else
	{
		domain_name = find_domain_name(url);
		newlink = (char*)calloc(strlen(link_name) + strlen(domain_name) + 2, 1);
		if (!newlink)
			return (1);
		strcpy(newlink, domain_name);
		if (strncmp("/", link_name, 1) != 0)
			strcat(newlink, "/");
		strcat(newlink, link_name);
		if (check_urls(newlink) == 1)
			link_handler(newlink, lvl + 1);
		free(newlink);
	}
	return (0);
}
int	link_searcher(TidyNode child, std::vector<TidyAttr> links)
{
	TidyAttr	href;

	href = tidyAttrGetById(child, TidyAttr_HREF);
	if (href)
		links.push_back(href);
	return (0);	
}
