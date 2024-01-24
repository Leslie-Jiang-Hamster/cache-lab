#include "common-types.h"
#include "cachelab.h"
#include "io.h"
#include "util.h"

int main(int argc, str_t argv[])
{
    flags_t flags = parse_flags(argc, argv);
    valgrind_seq_t valgrind_seq = read_valgrind(flags.file);
    memory_seq_t memory_seq = simplify_valgrind(valgrind_seq);
    result_t result = cache_sim(flags, memory_seq);
    printSummary(result.hit, result.miss, result.eviction);
    return 0;
}
