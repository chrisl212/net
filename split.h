/* split.h */

#define SPLIT_1 0 /* puts the delimiter in the first half */
#define SPLIT_2 1 /* puts the delimiter in the second half */
#define SPLIT_DELETE 2 /* puts the delimiter in neither half */

int split(char **s, char **dest, char *delim, int opt);
