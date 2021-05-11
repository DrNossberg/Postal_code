/*
** EPITECH PROJECT, 2018
** ex00
** File description:
** List delete
*/

#include <stdlib.h>
#include "list.h"

bool list_del_elem_at_front(list_t *front_ptr)
{
    node_t *node_del;

    if (!*front_ptr)
        return (false);
    node_del = *front_ptr;
    *front_ptr = node_del->next;
    free(node_del);
    return (true);
}

bool list_del_elem_at_back(list_t *front_ptr)
{
    node_t *penul_node;

    if (!*front_ptr)
        return (false);
    if (!(*front_ptr)->next) {
        free(*front_ptr);
        *front_ptr = NULL;
    } else {
        for (penul_node = *front_ptr; penul_node->next->next;
        penul_node = penul_node->next);
        free(penul_node->next);
        penul_node->next = NULL;
    }
    return (true);
}

bool list_del_elem_at_position(list_t *front_ptr, unsigned int position)
{
    unsigned int i = 0;
    node_t *penul_node;
    node_t *tmp_node;

    if (!position)
        return (list_del_elem_at_front(front_ptr));
    for (penul_node = *front_ptr; penul_node && i + 1 < position;
    penul_node = penul_node->next, i++);
    if (i + 1 != position)
        return (false);
    tmp_node = penul_node->next->next;
    free(penul_node->next);
    penul_node->next = tmp_node;
    return (true);
}
