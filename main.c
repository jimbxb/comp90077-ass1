/* 
COMP90077 - Assignment 1 - James Barnes (820946)
Main testing program
*/

#include "main.h"
#include "gen.h"
#include "treap.h"
#include "array.h"
#include <sys/time.h>

#define N_TESTS 50

static int lengths[] = { 100000, 200000, 500000, 800000, 1000000 }; 
static int percents[] = { 1, 5, 10, 50, 100 }; 

static seq_t *seq = NULL;

void test_1(ops_t ops, int n);
void test_2(ops_t ops, int delete_perc);
void test_3(ops_t ops, int search_perc);
void test_4(ops_t ops, int n);

int main(int argc, char *argv[]) {
    assert(seq = malloc(sizeof(seq_t) * 1000000));

    for (int j = 0; j < sizeof(lengths) / sizeof(lengths[0]); j++) {
        for (int i = 0; i < N_TESTS; i++) {
            srand(i);
            test_1(treap_ops, lengths[j]);
        }
    }

    for (int j = 0; j < sizeof(percents) / sizeof(percents[0]); j++) {
        for (int i = 0; i < N_TESTS; i++) {
            srand(i);
            test_2(treap_ops, percents[j]);
        }
    }

    for (int j = 0; j < sizeof(percents) / sizeof(percents[0]); j++) {
        for (int i = 0; i < N_TESTS; i++) {
            srand(i);
            test_3(treap_ops, percents[j]);
        }
    }

    for (int j = 0; j < sizeof(lengths) / sizeof(lengths[0]); j++) {
        for (int i = 0; i < N_TESTS; i++) {
            srand(i);
            test_4(treap_ops, lengths[j]);
        }
    }

    for (int j = 0; j < sizeof(lengths) / sizeof(lengths[0]); j++) {
        for (int i = 0; i < N_TESTS; i++) {
            srand(i);
            test_1(array_ops, lengths[j]);
        }
    }

    for (int j = 0; j < sizeof(percents) / sizeof(percents[0]); j++) {
        for (int i = 0; i < N_TESTS; i++) {
            srand(i);
            test_2(array_ops, percents[j]);
        }
    }

    for (int j = 0; j < sizeof(percents) / sizeof(percents[0]); j++) {
        for (int i = 0; i < N_TESTS; i++) {
            srand(i);
            test_3(array_ops, percents[j]);
        }
    }

    for (int j = 0; j < sizeof(lengths) / sizeof(lengths[0]); j++) {
        for (int i = 0; i < N_TESTS; i++) {
            srand(i);
            test_4(array_ops, lengths[j]);
        }
    }

    free(seq);
    exit(EXIT_SUCCESS);
}

void test_1(ops_t ops, int n) {
    gen_t *generator = gen_new(n);
    for (int i = 0; i < n; i++) {
        gen_insertion(generator, &seq[i]);
    }
    void *structure = ops.constructor();

    struct timeval start, end;
    gettimeofday(&start, NULL);
    for (int i = 0; i < n; i++) {
        structure = ops.insert(structure, seq[i].elem);
    }
    gettimeofday(&end, NULL);

    ops.destructor(structure);
    gen_free(generator);
    printf("%s 1,%d,%f\n", ops.name, n, 
           (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) * 1e-6);
}

void test_2(ops_t ops, int delete_percent) {
    int n = 1000000;
    gen_t *generator = gen_new(n); 
    for (int i = 0; i < n; i++) {
        int prob = rand() & ((1 << 20) - 1);
        if (prob < delete_percent * 1048) {
            gen_deletion(generator, &seq[i]);
        } else {
            gen_insertion(generator, &seq[i]);
        }
    }
    void *structure = ops.constructor();

    struct timeval start, end;
    gettimeofday(&start, NULL);
    for (int i = 0; i < n; i++) {
        if (seq[i].type == DELETE) {
            structure = ops.delete(structure, seq[i].key);
        } else {
            structure = ops.insert(structure, seq[i].elem);
        }
    }
    gettimeofday(&end, NULL);
    
    ops.destructor(structure);
    gen_free(generator);
    printf("%s 2,%0.2f%%,%f\n", ops.name, delete_percent / 10.0, 
           (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) * 1e-6);
}

void test_3(ops_t ops, int search_percent) {
    int n = 1000000;
    gen_t *generator = gen_new(n); 
    for (int i = 0; i < n; i++) {
        int prob = rand() & ((1 << 20) - 1);
        if (prob < search_percent * 1048) {
            gen_search(generator, &seq[i]);
        } else {
            gen_insertion(generator, &seq[i]);
        }
    }
    void *structure = ops.constructor();
    
    struct timeval start, end;
    gettimeofday(&start, NULL);
    for (int i = 0; i < n; i++) {
        if (seq[i].type == SEARCH) {
            ops.search(structure, seq[i].key);
        } else {
            structure = ops.insert(structure, seq[i].elem);
        }
    }
    gettimeofday(&end, NULL);
    
    ops.destructor(structure);
    gen_free(generator);
    printf("%s 3,%0.2f%%,%f\n", ops.name, search_percent / 10.0,
           (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) * 1e-6);
}

void test_4(ops_t ops, int n) {
    gen_t *generator = gen_new(n);
    for (int i = 0; i < n; i++) {        
        int prob = rand() & ((1 << 20) - 1);
        if (prob < 52428) {
            gen_deletion(generator, &seq[i]);
        } else if (prob < 104857) {
            gen_search(generator, &seq[i]);
        } else {
            gen_insertion(generator, &seq[i]);
        }
    }
    
    void *structure = ops.constructor();

    struct timeval start, end;
    gettimeofday(&start, NULL);
    for (int i = 0; i < n; i++) {
        if (seq[i].type == DELETE) {
            structure = ops.delete(structure, seq[i].key);
        } else if (seq[i].type == SEARCH) {
            ops.search(structure, seq[i].key);
        } else {
            structure = ops.insert(structure, seq[i].elem);
        }
    }
    gettimeofday(&end, NULL);

    ops.destructor(structure);
    gen_free(generator);
    printf("%s 4,%d,%f\n", ops.name, n, 
           (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) * 1e-6);
}
