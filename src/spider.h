#ifndef SPIDER_H
# define SPIDER_H

#include <curl/curl.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <tidy.h>
#include <tidybuffio.h>
#include <stdio.h>

size_t	writeCallback(void *rec, size_t size, size_t nmemb, void *userdata);
int	get_data_from_url(const char *url, TidyDoc *doc, TidyBuffer *docbuf, TidyBuffer *tidy_errbuff, int *err);
int		get_image_data_from_url(const char *url);
const char	*find_domain_name(const char *url);
int	link_handler(const char *url, int lvl);
void	link_searcher(TidyNode child, int lvl, const char *url);
void	html_data_parsing(TidyDoc doc, TidyNode tnod, int indent, int lvl, const char *url);

#endif
