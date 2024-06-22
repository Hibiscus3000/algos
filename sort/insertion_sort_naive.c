#include <stdio.h>
#include <string.h>

#define MAX_ARRAY_LENGTH 100

void swap(int* a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void insertion_sort(int *array, int size, int *sorted)
{
    memcpy(sorted, array, size * sizeof(int));
    for (int i = 1; i < size; ++i)
    {
        int j = i;
        while (j > 0 && sorted[j - 1] > sorted[j])
        {
            swap(sorted + j - 1, sorted + j);
            --j;
        }
    }
}

void sort_and_print(int *array, int size)
{
    int sorted[size];
    insertion_sort(array, size, sorted);

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