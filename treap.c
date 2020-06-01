/* 
COMP90077 - Assignment 1 - James Barnes (820946)
Implemntation of a treap
*/

#include "treap.h"

treap_t *treap_rotate_left(treap_t *t);
treap_t *treap_rotate_right(treap_t *t);
treap_t *treap_delete_rotate(treap_t *t);

treap_t *treap_new() {
    return NULL;
}

treap_t *treap_insert(treap_t *t, element_t *elem) {
    if (!t) {
        assert(t = malloc(sizeof(treap_t)));
        t->left = t->right = NULL;
        t->elem = elem;
        t->priority = rand();
        return t;
    }

    if (elem->key < t->elem->key
         || (elem->key == t->elem->key && elem->id < t->elem->id)) {
        t->left = treap_insert(t->left, elem);

        if (t->left->priority < t->priority) {
            t = treap_rotate_right(t);
        }
    } else {
        t->right = treap_insert(t->right, elem);

        if (t->right->priority < t->priority) {
            t = treap_rotate_left(t);
        }
    }

    return t;
}

treap_t *treap_delete(treap_t *t, int key) {
    treap_t *parent = NULL, *node = t;
    int left = 0;

    while (node && node->elem->key != key) {
        parent = node;
        left = (key < node->elem->key);
        if (left) {
            node = node->left;
        } else {
            node = node->right;
        }
    }

    if (!node) {
        return t;
    }

    if (t == node) {
        return treap_delete_rotate(node);   
    }

    node = treap_delete_rotate(node);

    if (parent) {
        if (left) {
            parent->left = node;
        } else {
            parent->right = node;
        }
    } 

    return t;
}

treap_t *treap_delete_rotate(treap_t *t) {
    if (!t) {
        return t;
    }

    treap_t *tmp;
    if (!t->left) {
        tmp = t->right;
        free(t);
        t = tmp;
    } else if (!t->right) {
        tmp = t->left;
        free(t);
        t = tmp;
    } else if (t->left->priority < t->right->priority) {
        t = treap_rotate_right(t);
        t->right = treap_delete_rotate(t->right);
    } else {
        t = treap_rotate_left(t);
        t->left = treap_delete_rotate(t->left);
    }

    return t;
}

element_t *treap_search(treap_t *t, int key) {
    while (t && t->elem->key != key) {
        if (key < t->elem->key) {
            t = t->left;
        } else {
            t = t->right;
        }
    }

    if (!t) {
        return NULL;
    }

    return t->elem;
}

void treap_print(treap_t *t, int indent) {
    for (int i = 0; i < indent; i++) printf("| ");
    if (t) {
        printf("%02d: %02d - %d\n", t->elem->id, t->elem->key, t->priority);
        treap_print(t->left, indent + 1);
        treap_print(t->right, indent + 1);
    } else { 
        printf("--\n");
    }
}

void treap_free(treap_t* t) {
    if (!t) return;

    treap_free(t->left);
    treap_free(t->right);
    free(t);
}

/*
  A            C
 / \          / \
B   C   =>   A   E
   / \      / \
  D   E    B   D
*/
treap_t *treap_rotate_left(treap_t *t) {
    treap_t *root = t->right;
    t->right = root->left;
    root->left = t;
    return root;
}

/*
    A          B
   / \        / \
  B   C  =>  D   A
 / \            / \
D   E          E   C
*/
treap_t *treap_rotate_right(treap_t *t) {
    treap_t *root = t->left;
    t->left = root->right;
    root->right = t;
    return root;
}

int treap_check(treap_t *t) {
    return !t || ((!t->left || (t->left->elem->key <= t->elem->key
                                && t->priority <= t->left->priority
                                && treap_check(t->left)))
                  && (!t->right || (t->right->elem->key > t->elem->key
                                    && t->priority <= t->right->priority
                                    && treap_check(t->right))));
}
