/* http_request.h */

struct http_request
{
	char *host;
	char *path;
	char *method;
};

struct http_request *http_requestCreateFromURL(char *url, char *method);
struct http_request *http_requestCreate(char *host, char *path, char *method);
