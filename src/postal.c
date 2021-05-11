/*
** IUT Nancy-Charlemagne, 2021
** Projet :
**    postal
** Author :
**    Antoine Orion
** File description :
**    Main file of the postal program
*/

#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>
#include <string.h>

#include "postal.h"
#include "utils/OCR.h"


element *create_element(char *str) {
    element *node = malloc(sizeof(element));

    if (!node)
        return (NULL);
    node->str = strdup(str);
    node->list = NULL;
    return (node);
}

void display_city(void *head) {
    for (list_t node = head; node; node = node->next) {
        printf("%s\n", ((element *)node->value)->str);
    }
}

void display_postcodes(void *node) {
    // printf("Postal code :  %s\n", ((element *)node)->str);
    printf("%s\n", ((element *)node)->str);
    display_city(((element *)node)->list);
}

int estrcmp(const void *a, const void *str) {
    return (strcmp(((element *)a)->str, str));
}

int compar(const void *a, const void *b) {
    return (strcmp(((element *)a)->str, ((element *)b)->str));
}

void free_list(list_t postcode) {
    element *node;
    element *city = NULL;

    while (postcode) {
        node = list_get_elem_at_back(postcode);
        while (node->list) {
            city = list_get_elem_at_back(node->list);
            free(city->str);
            free(city);
            list_del_elem_at_back(&(node->list));
        }
        free(node->str);
        free(node);
        list_del_elem_at_back(&postcode);
    }
    free(postcode);
}

int main(int argc, char *argv[])
{
    list_t postcode = NULL;
    element *node;
    fdstream *fs;
    char *c_postcode;
    char *line;
    char *city;

    if (argc < 2) {
        printf("Please pass a file as parameter : ./postal my_file\n");
        return (0);
    }
    fs = init(argv[1]);
    for (int  i = 0; (line = fs->getnextline(fs)); i++) {
        city = strtok(line, " ");
        c_postcode = strtok(NULL, " ");
        if (!city || !c_postcode)
            continue;
        if (!(node = list_find(postcode, c_postcode, &estrcmp))) {
            node = create_element(c_postcode);
            list_add_elem_sorted(&postcode, node, &compar);
        }
        list_add_elem_sorted(&node->list, create_element(city), &compar);
        free(line);
    }
    list_display_with_function(postcode, &display_postcodes);
    free(line);
    free_list(postcode);
    fs->destroy(fs);
}
