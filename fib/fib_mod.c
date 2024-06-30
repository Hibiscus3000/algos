
#include <assert.h>
#include <errno.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

struct range
{
    long long low;
    long long up;
};

typedef struct range trange;

long long get_count(trange *range)
{
    return range->up - range->low + 1;
}

void cleanup(long long **arr, long long arr_size)
{
    for (size_t i = 0; i < arr_size; ++i)
    {
        free(arr[i]);
    }
    free(arr);
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

trange parse_range(char *str)
{
    trange range;
    range.low = str_to_ll(str);
    for (int i = 0;; ++i)
    {
        if ('-' == str[i])
        {
            range.up = str_to_ll(str + i + 1);
            break;
        }
        if (0 == str[i])
        {
            range.up = range.low;
            break;
        }
    }
    if (range.low < 0 || range.up < 0)
    {
        fprintf(stderr, "Bouth bounds of range must not be negative!\n");
        abort();
    }
    if (range.up < range.low)
    {
        fprintf(stderr, "Lower bound must be lesser then upper bound\n");
        abort();
    }
    return range;
}

long long *fib_nums(trange *num_range, long long mod)
{
    long long *fib_ns = (long long *)malloc(sizeof(long long) * get_count(num_range));
    long long prev = 0;
    long long cur = 1;
    if (num_range->low == 0)
    {
        fib_ns[0] = prev;
    }
    if (num_range->low <= 1)
    {
        fib_ns[1 - num_range->low] = cur;
    }
    for (size_t i = 2; i <= num_range->up; ++i)
    {
        long long tmp = cur;
        cur += prev;
        cur %= mod;
        prev = tmp;
        if (i >= num_range->low)
        {
            fib_ns[i - num_range->low] = cur;
        }
    }
    return fib_ns;
}

long long **fib_nums_for_each_mod(trange *num_range, trange *mod_range)
{
    long long mod_count = get_count(mod_range);
    long long **fib_ns = (long long **)malloc(sizeof(long long *) * mod_count);
    for (size_t i = 0; i < mod_count; ++i)
    {
        fib_ns[i] = fib_nums(num_range, mod_range->low + i);
    }
    return fib_ns;
}

void print_fib_nums(long long *fib_ns, long long fib_ns_count)
{
    for (size_t i = 0; i < fib_ns_count; ++i)
    {
        printf("%lld ", fib_ns[i]);
    }
    printf("\n");
}

void print_fib_nums_for_each_mod(long long **fib_ns, long long fib_ns_count, trange *mod_range)
{
    long long mod_count = get_count(mod_range);
    if (1 == mod_count)
    {
        print_fib_nums(*fib_ns, fib_ns_count);
        return;
    }
    for (size_t i = 0; i < mod_count; ++i)
    {
        printf("m = %lld: ", mod_range->low + i);
        print_fib_nums(fib_ns[i], fib_ns_count);
    }
}

void count_and_print_fib_nums(trange *num_range, trange *mod_range)
{
    long long **fib_ns = fib_nums_for_each_mod(num_range, mod_range);
    print_fib_nums_for_each_mod(fib_ns, get_count(num_range), mod_range);
    cleanup(fib_ns, get_count(mod_range));
}

int main(int argc, char *argv[])
{
    if (3 != argc)
    {
        fprintf(stderr, "Usage: fib_mod <num_lower_bound>(-<num_upper_bound>) <mod_lower_bound>(-<mod_upper_bound>)\n%s%s",
                "Defaults: <num_upper_bound>=<num_lower_bound>, <mod_upper_bound>=<mod_lower_bound>\n",
                "Result: fib numbers mod <m> from <num_lower_bound> to <num_upper_bound>, where <m> is between <mod_lower_bound> and <mod_upper_bound>\n");
        abort();
    }

    trange num_range = parse_range(argv[1]);
    trange mod_range = parse_range(argv[2]);
    if (0 == mod_range.low)
    {
        fprintf(stderr, "mod can't be zero\n");
    }
    count_and_print_fib_nums(&num_range, &mod_range);
    return 0;
}