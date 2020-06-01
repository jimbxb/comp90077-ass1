/* 
COMP90077 - Assignment 1 - James Barnes (820946)
Header for data generator
*/

#ifndef GEN_H_
#define GEN_H_

#define N_elem 1000000
#define N_KEYS 10000000

#include "main.h"

typedef struct gen_t {
    int id;
    int max_elem;
    element_t *elem;
} gen_t;

typedef enum op_type { INSERT, DELETE, SEARCH } op_type;

typedef struct seq_t {
    op_type type;
    int key;
    element_t *elem;
} seq_t;

gen_t *gen_new(int max_elem);
element_t *gen_element(gen_t *gen);
void gen_insertion(gen_t *gen, seq_t *seq);
void gen_deletion(gen_t *gen, seq_t *seq);
void gen_search(gen_t *gen, seq_t *seq); 
void gen_free(gen_t *gen);

#endif // GEN_H_
