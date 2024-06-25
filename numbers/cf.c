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

long long eu_div(long long dividend, long long divider)
{
    assert(divider);
    long long result = dividend / divider;
    long long mod = dividend % divider;
    if (mod < 0)
    {
        if (result > 0)
        {
            ++result;
        }
        else
        {
            --result;
        }
    }
    return result;
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

void cf(long long x, long long y)
{
    if (0 == y)
    {
        printf("\n");
        return;
    }
    int mod = eu_mod(x, y);
    int div = eu_div(x, y);
    printf("%d ", div);
    cf(y, mod);
}

void init_check(long long divider)
{
    if (0 == divider)
    {
        printf("division by zero");
    }
}

int main(int argc, char *argv[])
{
    if (3 != argc)
    {
        fprintf(stderr, "Usage: cf <first number> <second number>\nResult: continued fraction of <first number>/<second number>\n");
        abort();
    }
    long long x = str_to_ll(argv[1]);
    long long y = str_to_ll(argv[2]);

    init_check(y);
    cf(x, y);
    return 0;
}