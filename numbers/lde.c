#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

struct lde_solution
{
    long long a;
    long long b;
    long long x;
    long long y;
    long long gcd;
};

struct uv_storage
{
    long long u_prev;
    long long v_prev;
    long long u;
    long long v;
};

typedef struct lde_solution tlde_solution;
typedef struct uv_storage tuv_storage;

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

int llsign(long long x)
{
    return x < 0 ? -1 : 1;
}

long long llabs(long long x)
{
    return llsign(x) * x;
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

void set_next_uv(tuv_storage *uv, long long u, long long v)
{
    uv->u_prev = uv->u;
    uv->v_prev = uv->v;
    uv->u = u;
    uv->v = v;
}

void count_next_uv(tuv_storage *uv, long long q)
{
    set_next_uv(uv, uv->u_prev + q * uv->u, uv->v_prev + q * uv->v);
}

tlde_solution lde(long long a, long long b)
{
    if (llabs(a) < llabs(b))
    {
        return lde(b, a);
    }
    tlde_solution lde_s;
    lde_s.a = a;
    lde_s.b = b;

    tuv_storage uv;
    uv.u_prev = 1;
    uv.v_prev = 0;
    uv.u = 0;
    uv.v = -1;

    int i;
    for (i = 0; 0 != b; ++i)
    {
        long long div = eu_div(a, b);
        long long mod = eu_mod(a, b);

        count_next_uv(&uv, div);

        a = b;
        b = mod;
    }

    if (1 == i)
    {
        uv.v_prev *= llsign(a);
    }

    lde_s.gcd = llabs(a);
    lde_s.x = uv.u_prev * (i % 2 ? -1 : 1);
    lde_s.y = uv.v_prev * (i % 2 ? -1 : 1);
    return lde_s;
}

void print_lde_solution(tlde_solution *lde_s)
{
    printf("gcd = %lld\n", lde_s->gcd);
    printf("x   = %lld\n", lde_s->x);
    printf("y   = %lld\n", lde_s->y);

    long long eq_res = lde_s->a * lde_s->x + lde_s->b * lde_s->y;
    printf("%lld * %lld + %lld * %lld = %lld\n", lde_s->a, lde_s->x, lde_s->b, lde_s->y, eq_res);
    if (eq_res == lde_s->gcd)
    {
        printf("CORRECT!\n");
    } else
    {
        printf("INCORRECT!\n");
    }
}

int main(int argc, char *argv[])
{
    if (3 != argc)
    {
        fprintf(stderr, "Usage: lde <a> <b>\nResult: greatest common divisor (<gcd>) of <a> and <b> %s",
                "and a particular solution of linear diophantine equation of <a>x + <b>y = <gcd>\n");
        abort();
    }
    long long a = str_to_ll(argv[1]);
    long long b = str_to_ll(argv[2]);

    tlde_solution lde_s = lde(a, b);
    print_lde_solution(&lde_s);

    return 0;
}