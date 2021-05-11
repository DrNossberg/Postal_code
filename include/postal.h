/*
** IUT Nancy-Charlemagne, 2021
** Projet :
**    postal
** Author :
**    Antoine Orion
** File description :
**    header file of the postal g̶a̶m̶e̶ program
*/

#ifndef POSTAL_H
#define POSTAL_H

#include "../lists/include/list.h"

typedef struct element {
    char    *str;
    list_t  list;
} element;

typedef element postal_code;
typedef element city;

#endif /* POSTAL_H */