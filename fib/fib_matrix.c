
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#define FIB_MATRIX_SIDE 2
#define FIB_MATRIX_SIZE (FIB_MATRIX_SIDE * FIB_MATRIX_SIDE)

long long str_to_ll(char *str)
{
    long long result = strtoll(str, NULL, 10);
    if (errno)
    {
        perror("strtoll");
        abort();
    }
    return result;
}

void one_matrix(long long* matrix)
{
    for (size_t i = 0; i < FIB_MATRIX_SIDE; ++i)
    {
        for (size_t j = 0; j < FIB_MATRIX_SIDE; ++j)
        {
            if (i == j)
            {
                matrix[i * FIB_MATRIX_SIDE + j] = 1;
            }
            else
            {
                matrix[i * FIB_MATRIX_SIDE + j] = 0;
            }
        }
    }
}

void matrix_prod(long long matrix1[FIB_MATRIX_SIZE], long long matrix2[FIB_MATRIX_SIZE], long long mod)
{
    long long matrix_result[FIB_MATRIX_SIZE] = {0};
    for (size_t i = 0; i < FIB_MATRIX_SIDE; ++i)
    {
        for (size_t k = 0; k < FIB_MATRIX_SIDE; ++k)
        {
            for (size_t j = 0; j < FIB_MATRIX_SIDE; ++j)
            {
                matrix_result[i * FIB_MATRIX_SIDE + j] += matrix1[i * FIB_MATRIX_SIDE + k] * matrix2[k * FIB_MATRIX_SIDE + j];
                matrix_result[i * FIB_MATRIX_SIDE + j] %= mod;
            }
        }
    }
    
    for (size_t i = 0; i < FIB_MATRIX_SIZE; ++i)
    {
        matrix1[i] = matrix_result[i];
    }
}

void matrix_pow(long long matrix[FIB_MATRIX_SIZE], long long exponent, long long mod)
{
    long long matrix_mult[] = {matrix[0], matrix[1], matrix[2], matrix[3]};
    one_matrix(matrix);
    while (exponent)
    {
        if (exponent % 2)
        {
            matrix_prod(matrix, matrix_mult, mod);
        }
        matrix_prod(matrix_mult, matrix_mult, mod);
        exponent /= 2;
    }
}

long long count_fib_number(long long number, long long mod)
{
    long long fib_matrix[] = {1, 1, 1, 0};
    matrix_pow(fib_matrix, number, mod);
    return fib_matrix[1];
}

int main(int argc, char *argv[])
{
    if (3 != argc)
    {
        fprintf(stderr, "Usage: fib_matrix <number> <mod>\nResult: <number>th fibonacci number taken modulo <mod>\n");
        abort();
    }

    long long num = str_to_ll(argv[1]);
    if (num < 0)
    {
        fprintf(stderr, "num should be positive\n");
        abort();
    }
    long long mod = str_to_ll(argv[2]);
    if (mod < 2)
    {
        fprintf(stderr, "mod should be greater then 1\n");
        abort();
    }

    long long fib_num = count_fib_number(num, mod);
    printf("%lld\n", fib_num);

    return 0;
}