#include "spider.h"

size_t	urls_size()
{
	size_t	i;

	i = 0;
	if (urls)
	{
		while (urls[i])
			i++;
	}
	return (i);
}

void	free_urls()
{
	int	i;

	i = 0;
	if (urls)
	{
		while (urls[i])
		{
			free(urls[i]);
			i++;
		}
	}
}

void	add_url(char *url)
{
	int	i;
	
	if (!urls)
	{
		urls = calloc(sizeof(char *), 8);
	}
	i = 0;
	while (urls[i])
		i++;
}
int	check_urls(char	*url)
{
	int	i;

	i = 0;
	if (urls)
	{
		while (strcmp(urls[i], url) != 0)
			i++;
		if (urls[i])
			return (0);
	}
	add_url(url);
	return (1);
}
