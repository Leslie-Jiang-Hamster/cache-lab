#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "io.h"
#include "util.h"
#include "common-types.h"

// tested
flags_t parse_flags(int argc, str_t argv[]) {
    int opt;
    flags_t flags;
    while ((opt = getopt(argc, argv, "s:E:b:t:")) != -1) {
        if (opt == 's') {
            flags.S = atoi(optarg);
        }
        else if (opt == 'E') {
            flags.E = atoi(optarg);
        }
        else if (opt == 'b') {
            flags.B = atoi(optarg);
        }
        else if (opt == 't') {
            flags.file = optarg;
        }
        else {
            err("invalid flag");
        }
    }
    return flags;
}

// tested
valgrind_atom_t read_valgrind_atom(buffer_t buffer) {
    char category;
    addr_t addr;
    int matched = sscanf(buffer, " %c %lx,%*d", &category, &addr);
    if (matched != 2) {
        err("valgrind line parsing failure (sscanf parsing failure)");
    }
    chk_category(category);
    valgrind_atom_t valgrind_atom = {
        .category = category,
        .addr = addr
    };
    return valgrind_atom;
}

// tested
valgrind_seq_t read_valgrind(str_t file) {
    valgrind_atom_t* seq = calloc(VALGRIND_SEQ_SIZE, sizeof(valgrind_atom_t));
    buffer_t buffer;
    int len = 0;
    file_ptr_t handle = fopen(file, "r");
    if (handle == NULL) {
        err("unable to open trace file");
    }
    while (fgets(buffer, sizeof(buffer), handle)) {
        if (buffer[0] == 'I') {
            continue;
        }
        seq[len] = read_valgrind_atom(buffer);
        len++;
    }
    fclose(handle);
    valgrind_seq_t valgrind_seq = {
        .seq = seq,
        .len = len
    };
    return valgrind_seq;
}

// tested
memory_seq_t simplify_valgrind(valgrind_seq_t valgrind_seq) {
    memory_seq_t memory_seq;
    int len = 0;
    memory_seq.seq = calloc(VALGRIND_SEQ_SIZE, sizeof(addr_t));
    for (int i = 0; i < valgrind_seq.len; i++) {
        if (valgrind_seq.seq[i].category == 'M') {
            memory_seq.seq[len] = valgrind_seq.seq[i].addr;
            len++;
        }
        memory_seq.seq[len] = valgrind_seq.seq[i].addr;
        len++;
    }
    memory_seq.len = len;
    free(valgrind_seq.seq);
    return memory_seq;
}