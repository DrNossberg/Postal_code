/*
** IUT Nancy-Charlemagne, 2021
** Projet :
**    postal
** Author :
**    Antoine Orion
** File description :
**    header file of the open/read/close utilitie
*/

#ifndef FILESTREAM
#define FILESTREAM

#include <stdio.h>

#define READ_CHUNK_SIZE 2000 //TODO if multi-threading implementation :
/* scale this number depending on the core number & filesize */

typedef struct filestream fdstream;
struct filestream {
    FILE    *fptr;
    char    *path;
    char    *content;
    unsigned int offset;
    // unsigned int padding; -> room for read optimisation ?

    size_t  (*read)  (fdstream *);
    char    *(*getnextline)(fdstream *);
    void    (*destroy) (fdstream *);
};

fdstream *init(char *path);
char *my_getline(fdstream *fs, unsigned int *llenght);
#endif /* FILESTREAM */