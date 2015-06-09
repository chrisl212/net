/* http_download.h */

#include "http_request.h"
#include "http_header.h"

typedef void (*http_downloadDataReceivedCallback)(struct http_header *header, char *data);

int http_downloadSyncWithRequest(struct http_request *req);
int http_downloadSyncWithURL(char *url, char *method);
void http_downloadSetDataReceivedCallback(http_downloadDataReceivedCallback func); 
