
#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define MIN_BASE 2
#define MAX_BASE 16

int convert_base(char *b)
{
    int base = strtol(b, NULL, 10);
    if (MAX_BASE < base || base < MIN_BASE)
    {
        fprintf(stderr, "Invalid base: %d. Base must in [%d, %d]", base, MIN_BASE, MAX_BASE);
        abort();
    }
    return base;
}

int translate_char(char c, int base)
{
    int result;
    if ('0' <= c && c <= '9')
    {
        result = c - '0';
    }
    if ('A' <= c && c <= 'F')
    {
        result = 10 + c - 'A';
    }
    if (result >= base)
    {
        fprintf(stderr, "Invalid digit %c in base %d number system\n", c, base);
        abort();
    }
    return result;
}

char translate_digit(int digit, int base)
{
    assert(0 <= digit && digit < base);
    if (0 <= digit && digit <= 9)
    {
        return '0' + digit;
    }
    if (10 <= digit && digit < 16)
    {
        return 'A' + digit - 10;
    }
    abort();
}

long long to10(char *num, int base)
{
    long long translated_number = 0;
    for (int i = 0;; ++i)
    {
        char current_char = num[i];
        if (!current_char)
        {
            return translated_number;
        }
        translated_number = base * translated_number + translate_char(current_char, base);
    }
    return translated_number;
}

long long get_length(long long number10, int base)
{
    int length = 0;
    while (number10 || number10 % base)
    {
        number10 /= base;
        ++length;
    }
    return length;
}

char *to_base(long long number10, int base)
{
    int length = get_length(number10, base);
    char *number_base = (char *)(malloc(sizeof(char) * length));

    for (int i = 0; i < length; ++i)
    {
        number_base[length - i - 1] = translate_digit(number10 % base, base);
        number10 /= base;
    }

    return number_base;
}

int main(int argc, char *argv[])
{
    if (4 != argc)
    {
        fprintf(stderr, "Usage: translation <number> <base from> <base to>\nResult: <number> in <base to>\n");
        abort();
    }

    int base_from = convert_base(argv[2]);
    int base_to = convert_base(argv[3]);
    char *number_base_from = argv[1];
    long long number10 = to10(number_base_from, base_from);
    char *number_base_to = to_base(number10, base_to);

    printf("%s(%d) = %s(%d)\n", number_base_from, base_from, number_base_to, base_to);
    free(number_base_to);

    return 0;
}