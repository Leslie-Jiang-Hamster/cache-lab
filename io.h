#include "common-types.h"

flags_t parse_flags(int argc, str_t argv[]);

valgrind_seq_t read_valgrind(str_t file);

valgrind_atom_t read_valgrind_atom(buffer_t buffer);

memory_seq_t simplify_valgrind(valgrind_seq_t valgrind_seq);