
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

long long pp(long long mod)
{
    assert(mod > 0);
    long long prev = 0;
    long long cur = 1 % mod;
    for (long long i = 2;; ++i)
    {
        long long tmp = cur;
        cur += prev;
        cur %= mod;
        prev = tmp;

        if (0 == prev && 1 % mod == cur)
        {
            return i - 1; 
        }
    }
}

int main(int argc, char* argv[])
{
    if (2 != argc)
    {
        fprintf(stderr, "Usage: pisano_period <mod>\nResult: pisano period of <mod>\n");
        abort();
    }

    long long mod = str_to_ll(argv[1]);
    if (mod <= 0)
    {
        fprintf(stderr, "mod must be positive\n");
        abort();
    }

    printf("Pi(%lld) = %lld\n", mod, pp(mod));

    return 0;
}