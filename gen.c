/* 
COMP90077 - Assignment 1 - James Barnes (820946)
Implementation of a data generator
*/

#include "gen.h"

int random(int lo, int hi) {
    int range = hi - lo + 1, n;
    if (range <= 0) return lo;
    int thresh = RAND_MAX / range * range;
    while ((n = rand()) > thresh);
    return (n % range) + lo;
}

gen_t *gen_new(int max_elem) {
    gen_t *gen;
    assert(gen = malloc(sizeof(gen_t)));
    gen->id = 1;
    gen->max_elem = max_elem;
    assert(gen->elem = malloc(max_elem * sizeof(element_t)));
    memset(gen->elem, 0, max_elem * sizeof(element_t));

    return gen;
}

element_t *gen_element(gen_t *gen) {
    assert(gen->id <= gen->max_elem);
    
    int id = gen->id++;

    gen->elem[id - 1].id = id;
    gen->elem[id - 1].key = random(0, N_KEYS);
    gen->elem[id - 1].deleted = 0;

    return &gen->elem[id - 1];
}

void gen_insertion(gen_t *gen, seq_t *seq) {
    seq->type = INSERT;
    seq->elem = gen_element(gen);
}

void gen_deletion(gen_t *gen, seq_t *seq) {
    seq->type = DELETE;

    int id = random(1, gen->id - 1);
    if (id < 1 || gen->elem[id - 1].deleted) {
        seq->key = random(0, N_KEYS);
    } else {
        gen->elem[id - 1].deleted = 1;
        seq->key = gen->elem[id - 1].key;
    }
}

void gen_search(gen_t *gen, seq_t *seq) {
    seq->type = SEARCH;
    seq->key = random(0, N_KEYS);
}

void gen_free(gen_t *gen) {
    free(gen->elem);
    free(gen);
}


