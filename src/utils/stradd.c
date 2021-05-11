/*
** IUT Nancy-Charlemagne, 2021
** Projet :
**    ls
** Author :
**    Antoine Orion
** add a str to the end of an other one
*/

#include <stdlib.h>
#include <string.h>

char *stradd(char *a, char *b) {
	int len    = strlen(a) + strlen(b);
	char *temp = malloc(sizeof(char) * (len + 2));

	temp = memset(temp, '\0', len + 1);
	strcat(strcat(temp, a), b);
    return(temp);
}

char * straddf(char *a, char *b) {
    char *tmp = stradd(a, b);

    free(a);
    free(b);
    return (tmp);
}
