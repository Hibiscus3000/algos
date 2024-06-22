#include <stdio.h>
#include <string.h>

#define MAX_ARRAY_LENGTH 100

void swap(int* a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void shaker_sort(int *array, int size, int *sorted)
{
    memcpy(sorted, array, size * sizeof(int));
    for (;;)
    {
        int number_of_shuffles = 0;
        for (int j = 0; j < size - 1; ++j)
        {
            if (sorted[j] > sorted[j + 1])
            {
                swap(sorted + j, sorted + j + 1);
                ++number_of_shuffles;
            }
        }
        if (!number_of_shuffles)
        {
            return;
        }

        number_of_shuffles = 0;
        for (int j = size - 2; j > -1; --j)
        {
            if (sorted[j] > sorted[j + 1])
            {
                swap(sorted + j, sorted + j + 1);
                ++number_of_shuffles;
            }
        }
    }
}

void sort_and_print(int *array, int size)
{
    int sorted[size];
    shaker_sort(array, size, sorted);

    for (int i = 0; i < size; ++i)
    {
        printf("%d ", array[i]);
    }
    printf("-> ");
    for (int i = 0; i < size; ++i)
    {
        printf("%d ", sorted[i]);
    }
    printf("\n");
}

int main()
{
    const int number_of_arrays = 4;
    int arrays[][MAX_ARRAY_LENGTH] = {{}, {1}, {6, 7, 2, 1, -1}, {4, 3, 1, -1, 5, 3, 1, 100, 1, 10}};
    int sizes[] = {0, 1, 5, 10};

    for (int i = 0; i < number_of_arrays; ++i)
    {
        sort_and_print(arrays[i], sizes[i]);
    }

    return 0;
}