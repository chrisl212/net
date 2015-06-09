/* http_header.c */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "http_header.h"
#include "split.h"

struct http_header *http_headerCreate(char *name, char *value, struct http_header *next)
{
	struct http_header *retval;

	retval = calloc(1, sizeof(struct http_header));
	if (name)
		retval->name = strdup(name);
	if (value)
		retval->value = strdup(value);
	retval->next = next;
	return retval;
}

int http_parseHeadersFromString(char *str, struct http_header **header)
{
	char *res, *temp, *delim, *val;
	int i, a;
	struct http_header *m, *n;	

	delim = "\r\n";
	temp = strdup(str);
	/* split(char **firstHalf, char **secondHalf, char *delim, int opt); */
	while ((split(&temp, &res, delim, SPLIT_DELETE)) == 0)
	{
		if (split(&temp, &val, ":", SPLIT_DELETE) == 0)
		{ 

			m->name = temp;
			m->value = val;

			n = http_headerCreate("", "", NULL);
			m->next = n;
			m = n;
		}
		else
		{

			*header = http_headerCreate("Response-Code", temp, NULL);

			m = http_headerCreate("", "", NULL);

			(*header)->next = m;
		}
		val = NULL;

		temp = strdup(res);

		res = NULL;
	}
	if (!m->name)
		free(m), m = NULL;

	return 0;
}
