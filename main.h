/* 
COMP90077 - Assignment 1 - James Barnes (820946)
Main testing program header
*/

#ifndef MAIN_H_
#define MAIN_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct element_t {
    int id;
    int key;
    int deleted;
} element_t;

typedef struct ops_t {
    char *name;
    void *(*constructor)();
    void (*destructor)(void *);
    void *(*insert)(void *, element_t *);
    void *(*delete)(void *, int);
    element_t *(*search)(void *, int);
} ops_t;

#endif // MAIN_H_