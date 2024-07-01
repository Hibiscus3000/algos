
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

struct num_in_fib_ns
{
    char *coefs;
    size_t coef_count;
    long long *terms;
    size_t term_count;
};

typedef struct num_in_fib_ns tnum_in_fib_ns;

void cleanup(tnum_in_fib_ns *expansion)
{
    free(expansion->coefs);
    free(expansion->terms);
}

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

tnum_in_fib_ns convert_to_fib_ns(long long number)
{
    tnum_in_fib_ns expansion;
    long long prev = 0;
    long long cur = 1;
    size_t i;

    for (i = 1; cur <= number; ++i)
    {
        long long tmp = cur;
        cur += prev;
        prev = tmp;
    }

    expansion.coef_count = i - 2;
    expansion.coefs = (char *)malloc(sizeof(char) * expansion.coef_count);
    expansion.term_count = 0;
    expansion.terms = (long long *)malloc(sizeof(long long) * expansion.coef_count);

    for (; i > 2; --i)
    {
        long long tmp = prev;
        prev = cur - prev;
        cur = tmp;
        if (cur <= number)
        {
            number -= cur;
            expansion.coefs[expansion.coef_count + 2 - i] = 1;
            expansion.terms[expansion.term_count] = cur;
            ++expansion.term_count;
        }
        else
        {
            expansion.coefs[expansion.coef_count + 2 - i] = 0;
        }
    }

    return expansion;
}

void print_number_in_fib(tnum_in_fib_ns *expansion, long long number)
{
    printf("%lld = %lld", number, expansion->terms[0]);
    for (size_t i = 1; i < expansion->term_count; ++i)
    {
        printf(" + %lld", expansion->terms[i]);
    }
    printf("\n");

    printf("%lld = (", number);
    for (size_t i = 0; i < expansion->coef_count; ++i)
    {
        printf("%d", expansion->coefs[i]);
    }
    printf(")f\n");
}

int main(int argc, char *argv[])
{
    if (2 != argc)
    {
        fprintf(stderr, "Usage: fib_ns <n>\nResult: <n> if fibonacci numeral system\n");
        abort();
    }
    long long num = str_to_ll(argv[1]);
    if (num <= 0)
    {
        fprintf(stderr, "number should be positive\n");
        abort();
    }
    tnum_in_fib_ns expansion = convert_to_fib_ns(num);
    print_number_in_fib(&expansion, num);
    cleanup(&expansion);
    return 0;
}