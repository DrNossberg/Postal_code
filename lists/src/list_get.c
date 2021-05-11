/*
** EPITECH PROJECT, 2018
** ex00
** File description:
** List Get
*/

#include <stdlib.h>
#include "list.h"

void *list_get_elem_at_front(list_t list) {
	return (list ? list->value : NULL);
}

void *list_get_elem_at_back(list_t list) {
	node_t *node;

	for (node = list; node->next; node = node->next);
	return (node->value);
}

void *list_get_elem_at_position(list_t list, unsigned int position) {
	unsigned int i = 0;
	node_t *node;

	if (list_is_empty(list))
		return (NULL);
	for (node = list; node->next && i < position; node = node->next, i++);
	return (i == position ? node->value : NULL);
}

void *list_find(list_t list, void * elem, int (*compar)(const void *a, const void *b)) {
	if (list_is_empty(list))
		return (NULL);
	for (node_t *node = list; node->next; node = node->next)
		if (!compar(node->value, elem))
			return (node->value);
	return (NULL);
}
