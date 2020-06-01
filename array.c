/* 
COMP90077 - Assignment 1 - James Barnes (820946)
Implemntation of a dynamic array, the competitor
*/

#include "array.h"

#define INIT_SIZE 4
#define GROWTH    2
#define SHRINK    4

array_t *array_new() {
    array_t *a;
    assert(a = malloc(sizeof(array_t)));
    a->n = 0;
    a->alloc = INIT_SIZE;
    assert(a->array = malloc(INIT_SIZE * sizeof(element_t*)));
    return a;
}

array_t *array_insert(array_t *a, element_t *elem) {
    if (a->n >= a->alloc) {
        a->alloc *= GROWTH;
        assert(a->array = realloc(a->array, a->alloc * sizeof(element_t*)));
    }
    
    a->array[a->n++] = elem;

    return a;
}

array_t *array_delete(array_t *a, int key) {
    for (int i = 0; i < a->n; i++) {
        if (a->array[i]->key == key) {
            a->array[i] = a->array[--a->n];

            if (a->n > INIT_SIZE && a->n < a->alloc / SHRINK) {
                a->alloc /= GROWTH;
                assert(a->array = realloc(a->array, 
                                          a->alloc * sizeof(element_t*)));
            }
            
            break;
        }
    }

    return a;
}
element_t *array_search(array_t *a, int key) {
    for (int i = 0; i < a->n; i++) {
        if (a->array[i]->key == key) {
            return a->array[i];
        }
    }

    return NULL;
}
void array_print(array_t* a, int indent) {
    printf("{ ");

    for (int i = 0; i < a->n - 1; i++) {
        printf("%02d: %02d, ", a->array[i]->id, a->array[i]->key);
    }

    if (a->n) {
        printf("%02d: %02d, ", 
               a->array[a->n - 1]->id, a->array[a->n - 1]->key);
    }

    printf(" }");
}

void array_free(array_t* a) {
    free(a->array);
    free(a);
}

