#include "common-types.h"
#include <stdlib.h>
#include "set.h"
#include "util.h"

cache_t Cache_init(int S, int E, int B) {
    cache_t cache;
    cache.S = S;
    cache.E = E;
    cache.B = B;
    cache.sets = calloc((1 << S), sizeof(set_t));
    for (int i = 0; i < (1 << S); i++) {
        cache.sets[i] = Set_init(E);
    }
    return cache;
}

result_t Cache_visit(cache_t cache, addr_t addr, int timestamp) {
    addr_t index = extract_index(cache, addr);
    addr_t tag = extract_tag(cache, addr);
    return Set_visit(cache.sets + index, tag, timestamp);
}