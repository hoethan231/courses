#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int *unsorted_array;
int *sorted_array;
int array_size;

// To pass parameters to sorting threads
typedef struct
{
    int start_index;
    int end_index;
} SortParams;

// Merge two sorted subarrays
void merge(int left_start, int left_end, int right_start, int right_end)
{
    int i = left_start;
    int j = right_start;
    int k = left_start;

    // Merge the two sorted subarrays
    while (i <= left_end && j <= right_end)
    {
        if (unsorted_array[i] <= unsorted_array[j])
        {
            sorted_array[k++] = unsorted_array[i++];
        }
        else
        {
            sorted_array[k++] = unsorted_array[j++];
        }
    }

    while (i <= left_end)
    {
        sorted_array[k++] = unsorted_array[i++];
    }

    while (j <= right_end)
    {
        sorted_array[k++] = unsorted_array[j++];
    }
}

// Quicksort for sublists
void quicksort(int start, int end)
{
    if (start < end)
    {
        int pivot = unsorted_array[end];
        int i = start - 1;

        for (int j = start; j < end; j++)
        {
            if (unsorted_array[j] <= pivot)
            {
                i++;
                int temp = unsorted_array[i];
                unsorted_array[i] = unsorted_array[j];
                unsorted_array[j] = temp;
            }
        }

        int temp = unsorted_array[i + 1];
        unsorted_array[i + 1] = unsorted_array[end];
        unsorted_array[end] = temp;

        int partition = i + 1;

        quicksort(start, partition - 1);
        quicksort(partition + 1, end);
    }
}

// Thread function for sorting
void *sorting_thread(void *params)
{
    SortParams *sort_params = (SortParams *)params;
    quicksort(sort_params->start_index, sort_params->end_index);
    pthread_exit(0);
}

// Thread function for merging
void *merging_thread(void *params)
{
    int mid = array_size / 2 - 1;
    merge(0, mid, mid + 1, array_size - 1);
    pthread_exit(0);
}

int main(int argc, char *argv[])
{
    // Check if array size is provided
    if (argc < 2)
    {
        printf("Usage: %s <array_size> [elements...]\n", argv[0]);
        return 1;
    }

    // Parse array size
    array_size = atoi(argv[1]);
    if (array_size <= 0)
    {
        printf("Array size must be positive.\n");
        return 1;
    }

    // Allocate memory for arrays
    unsorted_array = (int *)malloc(array_size * sizeof(int));
    sorted_array = (int *)malloc(array_size * sizeof(int));

    if (unsorted_array == NULL || sorted_array == NULL)
    {
        printf("Memory allocation failed.\n");
        return 1;
    }

    // Initialize array with command line arguments
    if (argc == 2 + array_size)
    {
        // Use provided values
        for (int i = 0; i < array_size; i++)
        {
            unsorted_array[i] = atoi(argv[i + 2]);
        }
    }

    // Print unsorted array
    printf("Unsorted array:\n");
    for (int i = 0; i < array_size; i++)
    {
        printf("%d ", unsorted_array[i]);
    }
    printf("\n");

    // Create threads
    pthread_t sort_thread1, sort_thread2, merge_thread;

    // Parameters for sorting threads
    SortParams sort_params1, sort_params2;
    sort_params1.start_index = 0;
    sort_params1.end_index = array_size / 2 - 1;

    sort_params2.start_index = array_size / 2;
    sort_params2.end_index = array_size - 1;

    // Create sorting threads
    pthread_create(&sort_thread1, NULL, sorting_thread, &sort_params1);
    pthread_create(&sort_thread2, NULL, sorting_thread, &sort_params2);

    // Wait for sorting threads to complete
    pthread_join(sort_thread1, NULL);
    pthread_join(sort_thread2, NULL);

    // Create merging thread
    pthread_create(&merge_thread, NULL, merging_thread, NULL);

    // Wait for merging thread to complete
    pthread_join(merge_thread, NULL);

    // Print sorted array
    printf("Sorted array:\n");
    for (int i = 0; i < array_size; i++)
    {
        printf("%d ", sorted_array[i]);
    }
    printf("\n");

    free(unsorted_array);
    free(sorted_array);

    return 0;
}