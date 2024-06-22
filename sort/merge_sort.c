#include <stdio.h>

#define MAX_ARRAY_LENGTH 100

void merge(int *left_side, int left_size, int *right_side, int right_size, int merged[])
{
    int left_idx = 0;
    int right_idx = 0;

    while (left_idx != left_size || right_idx != right_size)
    {
        if (left_idx == left_size || (right_idx != right_size && left_side[left_idx] > right_side[right_idx]))
        {
            merged[left_idx + right_idx] = right_side[right_idx];
            ++right_idx;
        }
        else
        {
            merged[left_idx + right_idx] = left_side[left_idx];
            ++left_idx;
        }
    }
}

void merge_sort(int *array, int size, int *sorted)
{
    if (size > 1)
    {
        int left_size = size / 2;
        int right_size = size - left_size;

        int left_side[left_size];
        int right_side[right_size];
        merge_sort(array, left_size, left_side);
        merge_sort(array + left_size, right_size, right_side);

        merge(left_side, left_size, right_side, right_size, sorted);
    }
    if (1 == size)
    {
        sorted[0] = array[0];
    }
}

void sort_and_print(int *array, int size)
{
    int sorted[size];
    merge_sort(array, size, sorted);

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
