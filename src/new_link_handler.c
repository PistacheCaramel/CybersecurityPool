#include "spider.h"

int	new_link(int lvl, const char *url, TidyAttr href)
{
	const char	*link_name;
	char	*newlink;
	const char	*domain_name;

	link_name = tidyAttrValue(href);
	if (strncmp(link_name, "https://", 8) == 0)
		link_handler(link_name, lvl + 1);
	else
	{
		domain_name = find_domain_name(url);
		newlink = calloc(strlen(link_name) + strlen(domain_name) + 2, 1);
		strcpy(newlink, domain_name);
		if (strncmp("/", link_name, 1) != 0)
			strcpy(newlink, "/");
		strcat(newlink, link_name);
		link_handler(newlink, lvl + 1);
	}
	return (0);
}
void	link_searcher(TidyNode child, int lvl, const char *url)
{
	TidyAttr	href;

	href = tidyAttrGetById(child, TidyAttr_HREF);
	if (href)
		new_link(lvl, url, href);			
}
