#include "common-types.h"
#include <stdlib.h>
#include "util.h"

result_t MISS = { 0, 1, 0 };
result_t HIT = { 1, 0, 0 };
result_t MISS_EVICTION = { 0, 1, 1 };

set_t Set_init(int E) {
    set_t set;
    set.E = E;
    set.len = 0;
    set.lines = calloc(E, sizeof(line_t));
    return set;
}

int Set_find(set_t set, addr_t tag) {
    for (int i = 0; i < set.len; i++) {
        if (set.lines[i].tag == tag) {
            return i;
        }
    }
    return -1;
}

int Set_LRU(set_t set) {
    int LRU = INF, pos;
    for (int i = 0; i < set.len; i++) {
        if (set.lines[i].timestamp < LRU) {
            LRU = set.lines[i].timestamp;
            pos = i;
        }
    }
    if (LRU == INF) {
        err("cannot find a timestamp less than INF");
    }
    return pos;
}

result_t Set_visit(set_t* set, addr_t tag, int timestamp) {
    result_t result = { 0, 0, 0 };
    int pos = -1;
    if ((pos = Set_find(*set, tag)) != -1) {
        result = Result_add(result, HIT);
        set->lines[pos].timestamp = timestamp;
    }
    else if (set->len < set->E) {
        result = Result_add(result, MISS);
        set->lines[set->len] = Line_init(tag, timestamp);
        (set->len)++;
    }
    else {
        result = Result_add(result, MISS_EVICTION);
        pos = Set_LRU(*set);
        set->lines[pos] = Line_init(tag, timestamp);
    }
    return result;
}