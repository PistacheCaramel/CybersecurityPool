#include "spider.h"

void   link_handler(const char *url, int lvl)
{
	struct s_data		html_data;

if (lvl > 5)
        return; 
    html_data = get_data_from_url(url);
    printf("size:%ld\n", html_data.size);
    if (html_data.data)
	html_data_parsing(html_data);
}

int main(int ac, char **av) {

   (void) ac;
    link_handler(av[1], 0);
}

