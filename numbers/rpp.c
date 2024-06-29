
#include <assert.h>
#include <errno.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

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

void check_positive(const char *var_name, long long val)
{
    if (val <= 0)
    {
        fprintf(stderr, "%s should be positive\n", var_name);
        abort();
    }
}

void check_not_zero(const char *var_name, long long val)
{
    if (val == 0)
    {
        fprintf(stderr, "%s shouldn't be zero\n", var_name);
        abort();
    }
}

long long rpp(long long base, long long exponent, long long mod)
{
    long long mult = base % mod;
    long long power = 1;
    while (exponent)
    {
        if (exponent % 2)
        {
            power = (power * mult) % mod;
        }
        mult = (mult * mult) % mod;
        exponent /= 2;
    }
    return power;
}

int main(int argc, char *argv[])
{
    if (4 != argc)
    {
        fprintf(stderr, "Usage: rpp <base> <exponent> <mod>\nResult: <base>^<exponent>");
        abort();
    }

    long long base = str_to_ll(argv[1]);
    long long exponent = str_to_ll(argv[2]);
    check_positive("exponent", exponent);
    check_not_zero("exponent", exponent);
    long long mod = str_to_ll(argv[3]);
    check_positive("mod", mod);

    long long power = rpp(base, exponent, mod);

    printf("(%lld^%lld)(%lld)=%lld\n", base, exponent, mod, power);

    return 0;
}
