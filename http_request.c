/* http_request.c */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "split.h"
#include "http_request.h"

struct http_request *http_requestCreate(char *host, char *path, char *method)
{
	struct http_request *retval;
	retval = calloc(1, sizeof(struct http_request));
	retval->host = strdup(host);
	retval->path = strdup(path);
	retval->method = strdup(method);
	return retval;
}

struct http_request *http_requestCreateFromURL(char *url, char *method)
{
	char *path;

	split(&url, &path, "/", SPLIT_2); /* stores hostname in url, path in path (SPLIT_2 preserves slash in path) */
	
	return http_requestCreate(url, path, method);
}
