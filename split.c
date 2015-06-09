/* split.c */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "split.h"

int split(char **s, char **dest, char *delim, int opt)
{
	size_t slen, delimlen;
	char *cmp, *srep;
	int i, c, d;
	size_t first_offset, second_offset;
	
	first_offset = 0, second_offset = 0;
	slen = strlen((*s));
	delimlen = strlen(delim);

	if (slen <= delimlen)
		return -1;	

	cmp = malloc(delimlen + 1);

	for (i = 0; i < slen - delimlen; i++)
	{
		for (c = 0; c < delimlen; c++)
			cmp[c] = (*s)[i + c]; 
		cmp[delimlen] = '\0';

		if (strcmp(cmp, delim) == 0)
		{
			switch(opt)
			{
				case SPLIT_1:
					first_offset = delimlen;
					second_offset = delimlen * -1;
					break;
				case SPLIT_2:
					second_offset = 0;
					break;
				case SPLIT_DELETE:
					second_offset = delimlen * -1;
					break;
				default:
					break;
			}; 
			(*dest) = malloc(slen - i + second_offset + 1);
			for (c = i - second_offset, d = 0; c < slen + 1; c++, d++)
				(*dest)[d] = (*s)[c]; 
			(*dest)[d] = '\0';
			srep = malloc(i + first_offset + 1);
			for (c = 0; c < i + first_offset; c++)
				srep[c] = (*s)[c];
			srep[c + 1] = '\0';
			*s = strdup(srep);
			free(cmp), free(srep);
			return 0;
		}
	}
	return -1;
}
