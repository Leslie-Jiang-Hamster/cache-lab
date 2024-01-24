#include "util.h"
#include "common-types.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "cache.h"

// tested
void err(str_t err_msg) {
    printf("error: %s\n", err_msg);
    exit(0);
}

void print_result(result_t result) {
    printf("%d %d %d\n", result.hit, result.miss, result.eviction);
}

void chk_category(char category) {
    if (category == 'M' || category == 'L' || category == 'S') {
        return;
    }
    err("invalid category");
}

line_t Line_init(addr_t tag, int timestamp) {
    line_t line = { tag, timestamp };
    return line;
}

// tested
result_t Result_add(result_t r1, result_t r2) {
    result_t result = { r1.hit + r2.hit, r1.miss + r2.miss, r1.eviction + r2.eviction };
    return result;
}

// tested
addr_t extract_index(cache_t cache, addr_t addr) {
    addr_t mask = (1 << cache.S) - 1;
    return (addr >> cache.B) & mask;
}

// tested
addr_t extract_tag(cache_t cache, addr_t addr) {
    return addr >> (cache.S + cache.B);
}

result_t cache_sim(flags_t flags, memory_seq_t memory_seq) {
    int S = flags.S;
    int E = flags.E;
    int B = flags.B;
    cache_t cache = Cache_init(S, E, B);
    result_t result = { 0, 0, 0 };
    for (int i = 0; i < memory_seq.len; i++) {
        result = Result_add(result, Cache_visit(cache, memory_seq.seq[i], i));
    }
    free(memory_seq.seq);
    for (int i = 0; i < (1 << cache.S); i++) {
        free(cache.sets[i].lines);
    }
    free(cache.sets);
    return result;
};