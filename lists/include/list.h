/*
** EPITECH PROJECT, 2018
** Generic List
** File description:
** Simple linked list of generic container
*/

#ifndef GENERIC_LIST_H_
#   define GENERIC_LIST_H_

#include <stdbool.h>

/*
** Types
*/

typedef struct node {
    void *value;
    struct node *next;
} node_t;

typedef node_t *list_t;

/*
** Functions
*/

/* Informations / Display */

unsigned int list_get_size(list_t list);
bool list_is_empty(list_t list);
void list_display(list_t list);
void list_display_with_function(list_t list, void (*display) (void*));

/* Modification */

bool list_add_elem_at_front(list_t *front_ptr, void *elem);
bool list_add_elem_at_back(list_t *front_ptr, void *elem);
bool list_add_elem_at_position(list_t *front_ptr, void *elem, unsigned int position);
bool list_add_elem_sorted(list_t *front_ptr, void *elem, int (*compar)(const void *, const void*));

bool list_del_elem_at_front(list_t *front_ptr);
bool list_del_elem_at_back(list_t *front_ptr);
bool list_del_elem_at_position(list_t *front_ptr, unsigned int position);

/* Getter */

void *list_get_elem_at_front(list_t list);
void *list_get_elem_at_back(list_t list);
void *list_get_elem_at_position(list_t list, unsigned int position);
void *list_find(list_t list, void * elem, int (*compar)(const void *a, const void *b));


#endif /* GENERIC_LIST_H_ */