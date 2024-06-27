#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

struct factorial
{
    int arg;
    long long value;
};

typedef struct factorial tfactorial;

void decrease_factorial(tfactorial *f)
{
    f->value /= f->arg--;
}

struct factorial_node
{
    int coef;
    int arg;
};

typedef struct factorial_node tfactorial_node;

struct factorial_expansion
{
    tfactorial_node *val;
    int size;
};

typedef struct factorial_expansion tfactorial_expansion;

void cleanup(tfactorial_expansion expansion)
{
    free(expansion.val);
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

tfactorial factorial_bigger_then(long long number)
{
    tfactorial f;
    f.value = 1;
    for (f.arg = 1;;)
    {
        if (0 == number / (f.value * (f.arg + 1)))
        {
            return f;
        }
        ++f.arg;
        f.value *= f.arg;
    }
}

tfactorial_expansion to_factorial(long long number)
{
    assert(number >= 0);
    tfactorial f = factorial_bigger_then(number);
    tfactorial_expansion factorial_expansion;
    factorial_expansion.val = (tfactorial_node *)malloc(sizeof(tfactorial_node) * f.arg);
    factorial_expansion.size = f.arg;

    for (; f.arg; decrease_factorial(&f))
    {
        factorial_expansion.val[f.arg - 1].arg = f.arg;
        factorial_expansion.val[f.arg - 1].coef = number / f.value;
        number %= f.value;
    }

    return factorial_expansion;
}

void print_factorial_dot(tfactorial_expansion factorial_expansion)
{
    for (int i = 0; i < factorial_expansion.size; ++i)
    {
        printf("%d.", factorial_expansion.val[i].coef);
    }
    printf("\n");
}

void print_factorial_expansion(tfactorial_expansion factorial_expansion)
{
    for (int i = 0; i < factorial_expansion.size; ++i)
    {
        if (i)
        {
            printf(" + ");
        }
        printf("%d * %d!", factorial_expansion.val[i].coef, factorial_expansion.val[i].arg);
    }
    printf("\n");
}

int main(int argc, char *argv[])
{
    if (2 != argc)
    {
        fprintf(stderr, "Usage: factorial <number>\nResult: <number> in factorial number system\n");
        abort();
    }

    long long number = str_to_ll(argv[1]);
    if (number < 0)
    {
        fprintf(stderr,"Number must be positive or zero\n");
        abort();
    }

    tfactorial_expansion factorial_expansion = to_factorial(number);
    print_factorial_dot(factorial_expansion);
    print_factorial_expansion(factorial_expansion);
    cleanup(factorial_expansion);

    return 0;
}