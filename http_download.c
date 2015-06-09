/* http_download.c */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include "http_download.h"
#include "split.h"

#define BLOCK_SIZE 128

http_downloadDataReceivedCallback dataReceivedCallback;

int http_downloadSyncWithRequest(struct http_request *req)
{
	struct http_header *header;
	struct addrinfo *res, hints;
	char *request, *retval, *tmp, *body;
	char buf[BLOCK_SIZE];
	int sock, bytes;
	
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	if ((getaddrinfo(req->host, "http", &hints, &res)) != 0)
	{
		return -1;
	}
	sock = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

	connect(sock, res->ai_addr, res->ai_addrlen);

	request = malloc(strlen(req->host) + strlen(req->path) + strlen(req->method) + 20);
	sprintf(request, "%s %s HTTP/1.1\r\nHost: %s\r\n\r\n", req->method, req->path, req->host);
	
	send(sock, request, strlen(request), 0);

	retval = "";
	while ((bytes = recv(sock, buf, BLOCK_SIZE, 0)) > 0)
	{
		tmp = strdup(retval);
		retval = malloc(strlen(retval) + bytes + 1);
		strcpy(retval, tmp);
		strcat(retval, buf);
		free(tmp);
	}

	close(sock);
	if (dataReceivedCallback)
	{
		split(&retval, &body, "\r\n\r\n", SPLIT_1);
		http_parseHeadersFromString(retval, &header);
		dataReceivedCallback(header, body);
	}
	return 0;
}

int http_downloadSyncWithURL(char *url, char *method)
{
	struct http_request *req = http_requestCreateFromURL(url, method);
	return http_downloadSyncWithRequest(req);
}
void http_downloadSetDataReceivedCallback(http_downloadDataReceivedCallback func)
{
	dataReceivedCallback = func;
}
