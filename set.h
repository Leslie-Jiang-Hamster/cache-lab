#include "common-types.h"

set_t Set_init(int E);

int Set_find(set_t set, addr_t tag);

int Set_LRU(set_t set);

result_t Set_visit(set_t* set, addr_t tag, int timestamp);