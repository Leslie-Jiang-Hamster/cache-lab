#include <stdint.h>
#include <stdio.h>

#ifndef COMMON_TYPES
    #define COMMON_TYPES
    #define BUFFER_SIZE 1024
    #define VALGRIND_SEQ_SIZE 1048576
    #define INF 100000000
    typedef char* str_t;
    typedef FILE* file_ptr_t;
    typedef char buffer_t[BUFFER_SIZE];
    typedef unsigned long addr_t;
    typedef struct {
        int S, E, B;
        str_t file;
    } flags_t;
    typedef struct {
        char category;
        addr_t addr;
    } valgrind_atom_t;
    typedef struct {
        valgrind_atom_t* seq;
        int len;
    } valgrind_seq_t;
    typedef struct {
        addr_t* seq;
        int len;   
    } memory_seq_t;
    typedef struct {
        int hit, miss, eviction;
    } result_t;
    typedef struct {
        addr_t tag;
        int timestamp;
    } line_t;
    typedef struct {
        int E, len;
        line_t* lines;
    } set_t;
    typedef struct {
        int S, E, B;
        set_t* sets;
    } cache_t;

#endif