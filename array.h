/* 
COMP90077 - Assignment 1 - James Barnes (820946)
Header for a dynamic array
*/

#ifndef ARRAY_H_
#define ARRAY_H_

#include "main.h"

typedef struct array_t array_t;

struct array_t {
    int n, alloc;
    element_t **array;
};

array_t *array_new();
array_t *array_insert(array_t *t, element_t *elem);
array_t *array_delete(array_t *t, int key);
element_t *array_search(array_t *t, int key);
void array_print(array_t* t, int indent);
void array_free(array_t* t);

static const ops_t array_ops = {
    "ARRAY",
    (void * (*)())&array_new, 
    (void (*)(void *))&array_free, 
    (void * (*)(void *, element_t *))&array_insert, 
    (void * (*)(void *, int))&array_delete, 
    (element_t * (*)(void *, int))&array_search
};

#endif // ARRAY_H_