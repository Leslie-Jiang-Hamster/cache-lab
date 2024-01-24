#include "common-types.h"
#include "stdbool.h"

void err(str_t err_msg);

void chk_category(char category);

result_t cache_sim(flags_t flags, memory_seq_t memory_seq);

line_t Line_init(addr_t tag, int timestamp);

result_t Result_add(result_t r1, result_t r2);

addr_t extract_index(cache_t cache, addr_t addr);

addr_t extract_tag(cache_t cache, addr_t addr);

void print_result(result_t result);