/* 
 * trans.c - Matrix transpose B = A^T
 *
 * Each transpose function must have a prototype of the form:
 * void trans(int M, int N, int A[N][M], int B[M][N]);
 *
 * A transpose function is evaluated by counting the number of misses
 * on a 1KB direct mapped cache with a block size of 32 bytes.
 */ 
#include <stdio.h>
#include "cachelab.h"

int is_transpose(int M, int N, int A[N][M], int B[M][N]);

/* 
 * transpose_submit - This is the solution transpose function that you
 *     will be graded on for Part B of the assignment. Do not change
 *     the description string "Transpose submission", as the driver
 *     searches for that string to identify the transpose function to
 *     be graded. 
 */
char transpose_32_32_desc[] = "Transpose 32*32";
void transpose_32_32(int M, int N, int A[N][M], int B[M][N])
{
    #define elif else if
    const int BSIZE = 8;
    int _M = M / BSIZE, _N = N / BSIZE, tmp, cnt = 0;
    int a0, a1, a2, a3, a4, a5, a6, a7;
    for (int i = 0; i < _N; i++) {
        for (int j = 0; j < _M; j++) {
            for (int _i = 0; _i < BSIZE; _i++) {
                for (int _j = 0; _j < BSIZE; _j++, cnt++) {
                    tmp = A[i * BSIZE + _i][j * BSIZE + _j];
                    if (cnt == 0) {
                        a0 = tmp;
                    }
                    elif (cnt == 1) {
                        a1 = tmp;
                    }
                    elif (cnt == 2) {
                        a2 = tmp;
                    }
                    elif (cnt == 3) {
                        a3 = tmp;
                    }
                    elif (cnt == 4) {
                        a4 = tmp;
                    }
                    elif (cnt == 5) {
                        a5 = tmp;
                    }
                    elif (cnt == 6) {
                        a6 = tmp;
                    }
                    else {
                        a7 = tmp;
                        cnt = -1;
                        B[j * BSIZE + _j - 7][i * BSIZE + _i] = a0;
                        B[j * BSIZE + _j - 6][i * BSIZE + _i] = a1;
                        B[j * BSIZE + _j - 5][i * BSIZE + _i] = a2;
                        B[j * BSIZE + _j - 4][i * BSIZE + _i] = a3;
                        B[j * BSIZE + _j - 3][i * BSIZE + _i] = a4;
                        B[j * BSIZE + _j - 2][i * BSIZE + _i] = a5;
                        B[j * BSIZE + _j - 1][i * BSIZE + _i] = a6;
                        B[j * BSIZE + _j][i * BSIZE + _i] = a7;
                    }
                }
            }
        }
    }    
}

char transpose_64_64_desc[] = "Transpose 64*64";
void transpose_64_64(int M, int N, int A[N][M], int B[M][N])
{
    #define elif else if
    const int BSIZE = 4;
    int _M = M / BSIZE, _N = N / BSIZE, tmp, cnt = 0;
    int a0, a1, a2, a3;
    for (int i = 0; i < _N; i++) {
        for (int j = 0; j < _M; j++) {
            for (int _i = 0; _i < BSIZE; _i++) {
                for (int _j = 0; _j < BSIZE; _j++, cnt++) {
                    tmp = A[i * BSIZE + _i][j * BSIZE + _j];
                    if (cnt == 0) {
                        a0 = tmp;
                    }
                    elif (cnt == 1) {
                        a1 = tmp;
                    }
                    elif (cnt == 2) {
                        a2 = tmp;
                    }
                    else {
                        a3 = tmp;
                        cnt = -1;
                        B[j * BSIZE + _j - 3][i * BSIZE + _i] = a0;
                        B[j * BSIZE + _j - 2][i * BSIZE + _i] = a1;
                        B[j * BSIZE + _j - 1][i * BSIZE + _i] = a2;
                        B[j * BSIZE + _j][i * BSIZE + _i] = a3;
                    }
                }
            }
        }
    }    
}

char transpose_submit_desc[] = "Transpose submission";
void transpose_submit(int M, int N, int A[N][M], int B[M][N]) {
    if (M == 32)
        transpose_32_32(M, N, A, B);
    else if (M == 64)
        transpose_64_64(M, N, A, B);
}

/* 
 * You can define additional transpose functions below. We've defined
 * a simple one below to help you get started. 
 */ 

/* 
 * trans - A simple baseline transpose function, not optimized for the cache.
 */
char trans_desc[] = "Simple row-wise scan transpose";
void trans(int M, int N, int A[N][M], int B[M][N])
{
    int i, j, tmp;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            tmp = A[i][j];
            B[j][i] = tmp;
        }
    }    

}

/*
 * registerFunctions - This function registers your transpose
 *     functions with the driver.  At runtime, the driver will
 *     evaluate each of the registered functions and summarize their
 *     performance. This is a handy way to experiment with different
 *     transpose strategies.
 */
void registerFunctions()
{
    /* Register your solution function */
    registerTransFunction(transpose_submit, transpose_submit_desc);

    /* Register any additional transpose functions */
    registerTransFunction(trans, trans_desc); 

}

/* 
 * is_transpose - This helper function checks if B is the transpose of
 *     A. You can check the correctness of your transpose by calling
 *     it before returning from the transpose function.
 */
int is_transpose(int M, int N, int A[N][M], int B[M][N])
{
    int i, j;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; ++j) {
            if (A[i][j] != B[j][i]) {
                return 0;
            }
        }
    }
    return 1;
}

