/*
** EPITECH PROJECT, 2018
** ex01
** File description:
** Simple List
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include "list.h"

unsigned int list_get_size(list_t list) {
    unsigned int size = 0;

    for (node_t *node = list; node; node = node->next, size++);
    return (size);
}

bool list_is_empty(list_t list) {
    return (list == NULL);
}

void list_display_with_function(list_t list, void (*display) (void*)) {
    for (node_t *node = list; node; node = node->next)
        display(node->value);
}


void list_display(list_t list) {
    for (node_t *node = list; node; node = node->next)
        printf("%p\n", node->value);
}
