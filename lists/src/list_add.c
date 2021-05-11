/*
** EPITECH PROJECT, 2018
** ex00
** File description:
** List Add
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include "list.h"

bool list_add_elem_at_front(list_t *front_ptr, void *elem) {
    node_t *new_node = malloc(sizeof(node_t));

    if (!new_node)
        return (false);
    new_node->next = *front_ptr;
    new_node->value = elem;
    *front_ptr = new_node;
    return (true);
}

bool list_add_elem_at_back(list_t *front_ptr , void *elem) {
    node_t *last_node;
    node_t *new_node;

    if (!(*front_ptr))
        return (list_add_elem_at_front(front_ptr, elem));
    new_node = malloc(sizeof(node_t));
    if (!new_node)
        return (false);
    for (last_node = *front_ptr; last_node->next; last_node = last_node->next);
    last_node->next = new_node;
    new_node->next = NULL;
    new_node->value = elem;
    return (true);
}

bool list_add_elem_at_position(list_t *front_ptr, void *elem,
unsigned int position) {
    unsigned int i = 0;
    node_t *new_node;
    node_t *pos_node;

    if (!position || !(*front_ptr)) 
        return (list_add_elem_at_front(front_ptr, elem));
    for (pos_node = *front_ptr; pos_node && i < position; pos_node = pos_node->next, i++);
    if (i != position || !(new_node = malloc(sizeof(node_t))))
        return (false);
    new_node->next = pos_node->next;
    new_node->value = elem;
    pos_node->next = new_node;
    return (true);
}

bool list_add_elem_sorted(list_t *front_ptr, void *elem, int (*compar)(const void *, const void*)) {
    for (list_t *node = front_ptr; *node; node = &(*node)->next)
        if (compar((*node)->value, elem) > 0)
            return (list_add_elem_at_position(node, elem, 0));
    return (list_add_elem_at_back(front_ptr, elem));
}
