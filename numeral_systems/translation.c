
#include <assert.h>
#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define MIN_BASE 2
#define MAX_BASE 36

#define DOT_NOT_FOUND -1
#define MAX_DIGITS_AFTER_DOT 100
#define FRACTION_ERROR 1e-13

struct number
{
    long long integer;
    double fraction;
};

typedef struct number tnumber;

int llsign(long long value)
{
    return value < 0 ? -1 : 1;
}

long long llabs(long long val)
{
    return llsign(val) * val;
}

char is_equal(double d1, double d2)
{
    return -FRACTION_ERROR < (d1 - d2) && (d1 - d2) < FRACTION_ERROR;
}

char is_zero(double d)
{
    return is_equal(d, 0);
}

char is_greater(double d1, double d2)
{
    return FRACTION_ERROR < (d1 - d2);
}

int translate_char(char c, int base)
{
    int result;
    if ('0' <= c && c <= '9')
    {
        result = c - '0';
    }
    else
    {
        result = 10 + c - 'A';
    }
    if (result < 0 || result >= base)
    {
        fprintf(stderr, "Invalid digit %c in base %d number system\n", c, base);
        abort();
    }
    return result;
}

char translate_digit(int digit, int base)
{
    assert(0 <= digit && digit < base);
    if (digit <= 9)
    {
        return '0' + digit;
    }
    if (10 <= digit)
    {
        return 'A' + digit - 10;
    }
    abort();
}

long long str_to_ll(char *str, int base)
{
    long long value = strtoll(str, NULL, base);
    if (errno)
    {
        perror("strtoll");
        abort();
    }
    return value;
}

int convert_base(char *str)
{
    int base = str_to_ll(str, 10);
    if (MAX_BASE < base || base < MIN_BASE)
    {
        fprintf(stderr, "Invalid base: %d. Base must in [%d, %d]\n", base, MIN_BASE, MAX_BASE);
        abort();
    }
    return base;
}

double convert_frac(char *str, int base)
{
    double frac = 0;
    long long divider = base;
    for (int i = 0;; ++i)
    {
        if (0 == str[i])
        {
            break;
        }
        frac += ((double)translate_char(str[i], base) / divider);
        divider *= base;
    }
    assert(is_greater(1, frac));
    return frac;
}

int find_dot(char *str)
{
    int dot_position = DOT_NOT_FOUND;
    for (int i = 0;; ++i)
    {
        if ('.' == str[i])
        {
            dot_position = i;
        }
        if (0 == str[i])
        {
            if (dot_position == i - 1)
            {
                return DOT_NOT_FOUND;
            }
            return dot_position;
        }
    }
}

tnumber convert_to_number(char *str, int base)
{
    tnumber num;
    num.integer = str_to_ll(str, base);

    int dot_position = find_dot(str);
    if (DOT_NOT_FOUND != dot_position)
    {
        num.fraction = convert_frac(str + dot_position + 1, base);
    }
    else
    {
        num.fraction = 0;
    }
    return num;
}

void print_int_part_in_base(long long int_part, int base)
{
    if (int_part / base)
    {
        print_int_part_in_base(int_part / base, base);
    }
    printf("%c", translate_digit(int_part % base, base));
}

void print_fraction_in_base(double fraction, int base)
{
    assert(is_greater(1, fraction));
    for (int i = 0; i < MAX_DIGITS_AFTER_DOT; ++i)
    {
        double power = pow(base, -i - 1);
        int digit_value = fraction / power;
        if (digit_value == base)
        {
            --digit_value; // in case of floating point errors
        }
        fraction -= digit_value * power;
        printf("%c", translate_digit(digit_value, base));
        if (is_zero(fraction))
        {
            break;
        }
    }
}

void print_number_in_base(tnumber *num, int base)
{
    if (num->integer < 0)
    {
        printf("-");
    }
    print_int_part_in_base(llabs(num->integer), base);
    if (!is_zero(num->fraction))
    {
        printf(".");
        print_fraction_in_base(num->fraction, base);
    }
    printf("\n");
}

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        fprintf(stderr, "Usage: translation <number> <base from> <base to>\nResult: <number> in <base to>\n");
        abort();
    }

    int base_from = convert_base(argv[2]);
    int base_to = convert_base(argv[3]);
    tnumber num = convert_to_number(argv[1], base_from);
    print_number_in_base(&num, base_to);
    return 0;
}