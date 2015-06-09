/* http_header.h */

struct http_header
{
	char *name;
	char *value;
	struct http_header *next;
};

struct http_header *http_headerCreate(char *name, char *value, struct http_header *next);
int http_parseHeadersFromString(char *, struct http_header **); /* header string must end in '\r\n', otherwise final header will not be parsed */
