#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "io.h"
#include "util.h"

void print_valgrind_atom(valgrind_atom_t valgrind_atom) {
    printf("category: %c\n", valgrind_atom.category);
    printf("addr: %lx\n", valgrind_atom.addr);
}

void test_read_valgrind() {
    valgrind_atom_t* seq = read_valgrind("traces/dave.trace").seq;
    int len = read_valgrind("traces/dave.trace").len;
    print_valgrind_atom(seq[0]);
    print_valgrind_atom(seq[1]);
    printf("%d\n", len);
}

void test_simplify_valgrind() {
    valgrind_seq_t valgrind_seq = read_valgrind("traces/yi.trace");
    memory_seq_t memory_seq = simplify_valgrind(valgrind_seq);
    for (int i = 0; i < memory_seq.len; i++) {
        printf("%lx\n", memory_seq.seq[i]);
    }
    printf("len: %d", memory_seq.len);
}

void test_result_add() {
    extern result_t MISS;
    extern result_t HIT;
    result_t r1 = MISS;
    result_t r2 = HIT;
    print_result(Result_add(Result_add(r1, r1), r2));
}

int main(int argc, str_t argv[]) {
    printf("--- test start ---\n");
    test_result_add(); 
    printf("--- test end ---\n");
    return 0;
}