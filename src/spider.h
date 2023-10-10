#ifndef SPIDER_H
# define SPIDER_H

#include <curl/curl.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <libxml/tree.h>
#include <libxml/parser.h>
#include <libxml/HTMLparser.h>


struct	s_data{
	char	*data;
	size_t	size;
};

size_t	writeCallback(void *rec, size_t size, size_t nmemb, void *userdata);
struct	s_data	get_data_from_url(const char *url);
void	link_handler(const char *url, int lvl);
int	html_data_parsing(struct s_data data);

#endif
