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
		free(urls);
	}
}

void	add_url(const char *url)
{
	int	i;
	
	i = 0;
	while (urls[i])
		i++;
	urls[i] = calloc(sizeof(char *), strlen(url) + 1);
	strcpy(urls[i], url); 
}

int	check_urls(const char	*url)
{
	int	i;

	i = 0;
	if (urls)
	{
		while (urls[i] && strcmp(urls[i], url) != 0)
			i++;
		if (urls[i])
			return (0);
	}
	if (urls_size() < 399)
		add_url(url);
	return (1);
}
