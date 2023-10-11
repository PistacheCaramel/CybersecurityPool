#include "spider.h"

const char	*find_domain_name(const char *url)
{
	char	*ptr;

	ptr = strstr(url, "//");
	if (ptr)
	{
		ptr++;
		if (ptr)
			ptr++;
		ptr = strstr((const char *)ptr, "/");
		if (ptr)
			*ptr = 0i;
	}
	return (url);
}

void	build_url(const char *img_url, const char *url)
{
	char	*dest;

	if (strncmp("https://", img_url, 8) == 0)
	{
		dest = (char *)img_url;
		get_image_data_from_url(dest);
		return ;
	}
	else
	{
		if (strncmp("/", img_url, 1) == 0)
		{
			dest = calloc(1, strlen(img_url) + strlen(url) + 1);
			if (dest)
			{
				strncpy(dest, find_domain_name(url), strlen(url));
				strcat(dest, img_url);
				printf("%s\n", dest);
			}
		}
		else
		{	
			dest = calloc(1, strlen(img_url) + strlen(url) + 2);
			if (dest)
			{
				strncpy(dest, find_domain_name(url), strlen(url));
				strcat(dest, "/");
				strcat(dest, img_url);
				printf("%s\n", dest);
			}
		}
	}	
	get_image_data_from_url(dest);
	free(dest);
}

int	get_img_attr(TidyNode child, const char *url)
{
	TidyAttr	attr;

	attr = tidyAttrFirst(child);
	while (attr)
	{
		if (strstr(tidyAttrName(attr), "src"))
		{
			printf("attr_name:%s\nurlimg:%s\n", tidyAttrName(attr), tidyAttrValue(attr));
			build_url(tidyAttrValue(attr), url);
			break;
		}
		attr = tidyAttrNext(attr);
	}
	return (0);
}

void	html_data_parsing(TidyDoc doc, TidyNode tnod, int indent, int lvl, const char *url)
{
	TidyNode child;

	(void) lvl;
	child = tidyGetChild(tnod);
	while (child)
	{
		ctmbstr name = tidyNodeGetName(child);
		if (name)	/* if it has a name, then it's an HTML tag ... */
		{
			link_searcher(child, lvl, url);
			if (strcmp("img", name) == 0)
				get_img_attr(child, url);

		}
 		html_data_parsing(doc, child, indent + 4, lvl, url);
		child = tidyGetNext(child);
		//recursive
	}
  /*for(child = tidyGetChild(tnod); child; child = tidyGetNext(child) ) {
    ctmbstr name = tidyNodeGetName(child);
    if(name) {
      TidyAttr attr;
      printf("%*.*s%s ", indent, indent, "<", name);
      for(attr = tidyAttrFirst(child); attr; attr = tidyAttrNext(attr) ) {
        printf("%s", tidyAttrName(attr));
        tidyAttrValue(attr)?printf("=\"%s\" ",
                                   tidyAttrValue(attr)):printf(" ");
      }
      printf(">\n");
    }
    else {
      TidyBuffer buf;
      tidyBufInit(&buf);
      tidyNodeGetText(doc, child, &buf);
      printf("%*.*s\n", indent, indent, buf.bp?(char *)buf.bp:"");
      tidyBufFree(&buf);
    }*/
  
}
