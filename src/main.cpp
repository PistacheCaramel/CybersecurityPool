#include <iostream>
#include <curl/curl.h>
#include <vector>
#include <string>
#include <string.h>
#include <fstream>
#include <libxml/tree.h>
#include <libxml/parser.h>
#include <libxml/HTMLparser.h>



// Fonction de rappel pour traiter les données reçues par libcurl
size_t writeCallback(char *ptr, size_t size, size_t nmemb, std::string* userdata) {
    size_t total_size = size * nmemb;
    userdata->append(ptr, total_size);
    return total_size;
}

size_t WriteImageCallback(void* ptr, size_t size, size_t nmemb, void* userp) {
    size_t total_size = size * nmemb;
    std::ofstream* file = static_cast<std::ofstream*>(userp);
    if (file && file->is_open()) {
        file->write(static_cast<const char*>(ptr), total_size);
    }
    return total_size;
}

void		get_image_data_from_url(std::string url)
{

	std::cout << "Url:" << url << std::endl;
    CURL* curl = curl_easy_init();
    if (!curl) {
        std::cerr << "Erreur lors de l'initialisation de libcurl" << std::endl;
        return ;
    }
    // Set request
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
 std::ofstream outputFile("1", std::ios::binary);

    if (!outputFile.is_open()) {
        std::cerr << "Erreur lors de l'ouverture du fichier local" << std::endl;
        return ;
    }
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteImageCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &outputFile);

    // Exécution de la requête
    CURLcode res = curl_easy_perform(curl);

    // Vérification des erreurs
    if (res != CURLE_OK) {
        std::cerr << "Erreur lors de la requête : " << curl_easy_strerror(res) << std::endl;
    } else {
        std::cout << "Image téléchargée avec succès et sauvegardée dans : " << "1" << std::endl;
    }

    // Nettoyage et libération des ressources
    curl_easy_cleanup(curl);

    // Fermeture du fichier local
    outputFile.close();

}
const char	*get_data_from_url(std::string url)
{   
    // libcurl Initialize
	std::cout << "Url:" << url << std::endl;
    CURL* curl = curl_easy_init();
    if (!curl) {
        std::cerr << "Erreur lors de l'initialisation de libcurl" << std::endl;
        return NULL;
    }

    // Set request
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

    // Save the data in a string
    std::string response;
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    // Execute the request
    CURLcode res = curl_easy_perform(curl);

    // Error check
    if (res != CURLE_OK) {
        std::cerr << "Erreur lors de la requête : " << curl_easy_strerror(res) << std::endl;
    	curl_easy_cleanup(curl);
	return (NULL);
    }
    curl_easy_cleanup(curl);
    return (response.c_str());
}

void   link_handler(std::string url, int lvl)
{
//    	std::vector<std::string>	img_links;
	const char			*html_data;
//	std::vector<std::string>::iterator	it;
//	std::vector<const char *>		imgs_data;
//	size_t				pos;
	htmlDocPtr			html_doc;
	xmlNodePtr			node;

    if (lvl > 5)
        return; 
    html_data = get_data_from_url(url);
    html_doc = htmlReadMemory(html_data, strlen(html_data), NULL, NULL, HTML_PARSE_RECOVER | HTML_PARSE_NOERROR);
    xmlNodePtr rootNode = xmlDocGetRootElement(html_doc);
    node = rootNode;
    while (node)
	{
		if (node->type == XML_ELEMENT_NODE)
		{
			if (xmlStrcmp(node->name, (const xmlChar*)"img") == 0)
			{
			 	std::cout << node->properties << std::endl;
			 }
		}
		node = node->next;
	}

/*    if (html_data.empty())
		return (NULL);
	while ((pos = html_data.find("<img", pos)) != std::string::npos)
	{
		pos = html_data.find("src", pos);
		pos = html_data.find_first_of("\"", pos);
		std::cout << "test:" << html_data.substr(pos - 4, 15) << std::endl;
		img_links.push_back(html_data.substr(pos + 1, ((html_data.find_first_of("\"", pos + 1) - pos) - 1) ));
		pos++;
	}
	it = img_links.begin();
	it++;
	while (it != img_links.end())
	{
		std::string	url_img_formatted = "https:";
		
		if ((*it).find("https", 0) == std::string::npos)
		{
			url_img_formatted.append(*it);
			get_image_data_from_url(url_img_formatted);
		}
		else
			get_image_data_from_url(*it);
		std::cout << *it << std::endl;
		it++;
	}*/
 
    return ;
}

int main(int ac, char **av) {

   (void) ac;
    link_handler(av[1], 0);
}
	
