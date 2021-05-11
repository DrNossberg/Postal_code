/*
** IUT Nancy-Charlemagne, 2021
** Projet :
**    postal
** Author :
**    Antoine Orion
** File description :
**    Implementation of the open/read/close utilities.
**	  This implementation "object-like" is unecessary, overcomplicated and doesn't add
**	  anythine to the program. Moreover, the getline function are just reimplementation of
**	  the standart lib getline(). Well, I just do to show off what I can do. Moreover, this could
**	  potentially make the implementation of multi-threading a little bit easier.
*/


#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>

#include "OCR.h"

char *straddf(char *a, char *b);


// static unsigned int get_filesize(char *path) { //TODO -> optimize READ_CHUNK_SIZE by scaling it to the size of the file
// 	struct stat st;

// 	stat(path, &st);
// 	return (st.st_size);
// }

size_t read(fdstream *fs) {
	size_t bt_read = fread(fs->content, sizeof(char), READ_CHUNK_SIZE, fs->fptr);
	fs->content[bt_read] = '\0';
	fs->offset = 0;
	// printf("bt_read : %u\n", bt_read);
	return (bt_read);
}

static unsigned int get_line_length(char *content, int offset) {
	unsigned int i = 0;

	if (!content)
		return(0);
	for (; content && content[offset + i] && content[offset + i] != '\n' && offset + i < READ_CHUNK_SIZE; i++);	
	return (i);
}

char *my_getline(fdstream *fs, unsigned int *llenght) {
	char *line = NULL;

	*llenght = get_line_length(fs->content, fs->offset);
	line = strndup(fs->content + fs->offset, *llenght);
	fs->offset += *llenght;
	line[*llenght] = '\0';
	return (line);
}

char *getnextline(fdstream *fs) { // issue when reaching EOF
	unsigned int llenght =  get_line_length(fs->content, fs->offset);
	char *line = NULL;

	if (!llenght && !fs->read(fs))
			return (NULL);
	line = my_getline(fs, &llenght);
	while (fs->content[fs->offset] != '\n' && (fs->offset == READ_CHUNK_SIZE
		|| fs->content[fs->offset] != '\0')) {
		if (fs->offset + llenght == READ_CHUNK_SIZE && !fs->read(fs))
			return (line);
		line = straddf(line, my_getline(fs, &llenght));
	}
	fs->content[fs->offset++] = '\0';
	return (line);
}

void destroy(fdstream *fs) {
	fclose(fs->fptr);
	free(fs->content);
	free(fs->path);
	free(fs);
}

fdstream *init(char *path) {
	fdstream *fs = malloc(sizeof(fdstream));

	if (!fs || !(fs->content = malloc(sizeof(char) * (READ_CHUNK_SIZE + 1)))) {
		printf("%s\n", "Error allocating memory"); //TODO better error handing strerror(errno)
		exit(EXIT_FAILURE);
	}
	memset(fs->content, '\0', READ_CHUNK_SIZE + 1);
	fs->fptr = fopen(path,"rb");
	if (!(fs->fptr)) {
		printf("%s\n", "Error opening file");
		exit(EXIT_FAILURE);
	}
	fs->path = strdup(path);
	fs->read = &read;
	fs->destroy = &destroy;
	fs->getnextline = &getnextline;
	fs->offset = 0;
	return (fs);
}

