#include "spider.h"


int	get_nodes(htmlDocPtr html_doc)
{
	(void) html_doc;
	return (0);
}
int	html_data_parsing(struct s_data data)
{
	htmlDocPtr	html_doc;

	if (data.data)
	{
		html_doc = htmlReadMemory(data.data, data.size, NULL, NULL, HTML_PARSE_RECOVER | HTML_PARSE_NOERROR);
		free(data.data);
	}
	get_nodes(html_doc);
	xmlFreeDoc(html_doc);
	xmlCleanupParser();
	return (0);
}
