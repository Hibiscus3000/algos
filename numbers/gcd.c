#include <assert.h>
#include <errno.h>
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

long long llabs(long long x)
{
    return x < 0 ? -x : x;
}

long long eu_mod(long long dividend, long long divider)
{
    assert(divider);
    long long result = dividend % divider;
    if (result < 0)
    {
        result += llabs(divider);
    }
    return result;
}

long long gcd(long long x, long long y)
{
    if (0 == x && y != 0)
    {
        return llabs(y);
    }
    if (y == 0)
    {
        return llabs(x);
    }
    int result = eu_mod(x, y);
    return gcd(y, result);
}

int main(int argc, char *argv[])
{
    if (3 != argc)
    {
        fprintf(stderr, "Usage: gcd <first number> <second number>\nResult: greatest common divisor of first and second numbers\n");
        abort();
    }
    long long x = str_to_ll(argv[1]);
    long long y = str_to_ll(argv[2]);

    printf("%lld\n", gcd(x, y));
    return 0;
}