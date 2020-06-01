/* 
COMP90077 - Assignment 1 - James Barnes (820946)
Header for treap
*/

#ifndef TREAP_H_
#define TREAP_H_

#include "main.h"

typedef struct treap_t treap_t;

struct treap_t {
    treap_t *left;
    treap_t *right;
    element_t *elem;
    int priority;
};

treap_t *treap_new();
treap_t *treap_insert(treap_t *t, element_t *elem);
treap_t *treap_delete(treap_t *t, int key);
element_t *treap_search(treap_t *t, int key);
void treap_print(treap_t* t, int indent);
void treap_free(treap_t* t);
int treap_check(treap_t *t);

static const ops_t treap_ops = {
    "TREAP",
    (void * (*)())&treap_new, 
    (void (*)(void *))&treap_free, 
    (void * (*)(void *, element_t *))&treap_insert, 
    (void * (*)(void *, int))&treap_delete, 
    (element_t * (*)(void *, int))&treap_search
};

#endif // TREAP_H_