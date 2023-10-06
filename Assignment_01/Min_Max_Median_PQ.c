#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define kUSER_INPUT_SIZE 64
#define kHEAP_CAPACITY 500000

static char user_input[kUSER_INPUT_SIZE];

void swap(int *lnum, int *rnum)
{
    const int temp = *lnum;
    *lnum = *rnum;
    *rnum = temp;
    return;
}

typedef struct
{
    int size;
    int array[kHEAP_CAPACITY];
} min_heap;

void init_min_heap(min_heap *min_heap_ptr)
{
    min_heap_ptr->size = 0;
    return;
}

void insert_min_heap(min_heap *min_heap_ptr, const int element)
{
    int *heap_array = min_heap_ptr->array;
    int *heap_size = &min_heap_ptr->size;
    heap_array[*heap_size] = element;
    (*heap_size)++;

    int now_idx = *heap_size - 1;
    int parent_idx = (now_idx - 1) >> 1;

    while (now_idx > 0 && heap_array[now_idx] < heap_array[parent_idx])
    {
        swap(&heap_array[now_idx], &heap_array[parent_idx]);
        now_idx = parent_idx;
        parent_idx = (now_idx - 1) >> 1;
    }
    return;
}
//+1 size, valid size
const int delete_min_heap(min_heap *min_heap_ptr)
{
    int *heap_array = min_heap_ptr->array;
    int *heap_size = &min_heap_ptr->size;
    swap(&heap_array[0], &heap_array[*heap_size - 1]);
    (*heap_size)--;

    int now_idx = 0;
    int left_idx = 2 * now_idx + 1;
    int right_idx = 2 * now_idx + 2;

    while (left_idx < *heap_size)
    {
        int compare_idx;
        if (right_idx < *heap_size)
        {
            compare_idx = heap_array[left_idx] < heap_array[right_idx] ? left_idx : right_idx;
        }
        else
        {
            compare_idx = left_idx;
        }

        if (heap_array[now_idx] < heap_array[compare_idx])
        {
            break;
        }
        swap(&heap_array[now_idx], &heap_array[compare_idx]);
        now_idx = compare_idx;
        left_idx = 2 * now_idx + 1;
        right_idx = 2 * now_idx + 2;
    }
    return heap_array[*heap_size];
}
//-1 size, empty 검사는 pq 에서 함
const int find_min_heap(min_heap *min_heap_ptr)
{
    return min_heap_ptr->array[0];
}
// empty 검사는 pq 에서 함
typedef struct
{
    int size;
    int array[kHEAP_CAPACITY];
} max_heap;

void init_max_heap(max_heap *max_heap_ptr)
{
    max_heap_ptr->size = 0;
    return;
}

void insert_max_heap(max_heap *max_heap_ptr, const int element)
{
    int *heap_array = max_heap_ptr->array;
    int *heap_size = &max_heap_ptr->size;
    heap_array[*heap_size] = element;
    (*heap_size)++;

    int now_idx = *heap_size - 1;
    int parent_idx = (now_idx - 1) >> 1;

    while (now_idx > 0 && heap_array[now_idx] > heap_array[parent_idx])
    {
        swap(&heap_array[now_idx], &heap_array[parent_idx]);
        now_idx = parent_idx;
        parent_idx = (now_idx - 1) >> 1;
    }
    return;
}

const int delete_max_heap(max_heap *max_heap_ptr)
{
    int *heap_array = max_heap_ptr->array;
    int *heap_size = &max_heap_ptr->size;
    swap(&heap_array[0], &heap_array[*heap_size - 1]);
    (*heap_size)--;

    int now_idx = 0;
    int left_idx = 2 * now_idx + 1;
    int right_idx = 2 * now_idx + 2;

    while (left_idx < *heap_size)
    {
        int compare_idx;
        if (right_idx < *heap_size)
        {
            compare_idx = heap_array[left_idx] > heap_array[right_idx] ? left_idx : right_idx;
        }
        else
        {
            compare_idx = left_idx;
        }

        if (heap_array[now_idx] > heap_array[compare_idx])
        {
            break;
        }
        swap(&heap_array[now_idx], &heap_array[compare_idx]);
        now_idx = compare_idx;
        left_idx = 2 * now_idx + 1;
        right_idx = 2 * now_idx + 2;
    }
    return heap_array[*heap_size];
}
// empty 검사는 pq 에서 함
const int find_max_heap(max_heap *max_heap_ptr)
{
    return max_heap_ptr->array[0];
}
// empty 검사는 pq 에서 함
typedef struct
{
    int size;
    max_heap left_heap;
    min_heap right_heap;
} median_heap;

void init_median_heap(median_heap *median_heap_ptr)
{
    median_heap_ptr->size = 0;
    init_max_heap(&median_heap_ptr->left_heap);
    init_min_heap(&median_heap_ptr->right_heap);
}

void insert_median_heap(median_heap *median_heap_ptr, const int element)
{
    int *heap_size = &median_heap_ptr->size;

    max_heap *left_heap = &median_heap_ptr->left_heap;
    min_heap *right_heap = &median_heap_ptr->right_heap;

    const int pivot = find_max_heap(&median_heap_ptr->left_heap);


    // while(1)
    // valid value check move left heap to right heap

    // while(1)
    // valid value check move right heap to left heap
}

const int delete_median_heap(median_heap *median_heap_ptr) {}
// empty 검사는 pq 에서 함
const int find_median_heap(median_heap *median_heap_ptr)
{
    return find_max_heap(&median_heap_ptr->left_heap);
}
// empty 검사는 pq 에서함

typedef struct
{
    int size;
    min_heap min_pq;
    max_heap max_pq;
    median_heap median_pq;

    min_heap deleted_min_pq;
    max_heap deleted_max_pq;
    max_heap deleted_left_median_pq;
    min_heap deleted_right_median_pq;
} priority_queue;

void init_pq(priority_queue *pq_ptr)
{
    pq_ptr->size = 0;
    init_min_heap(&pq_ptr->min_pq);
    init_max_heap(&pq_ptr->max_pq);
    init_median_heap(&pq_ptr->median_pq);

    init_min_heap(&pq_ptr->deleted_min_pq);
    init_max_heap(&pq_ptr->deleted_max_pq);
    init_max_heap(&pq_ptr->deleted_left_median_pq);
    init_min_heap(&pq_ptr->deleted_right_median_pq);
}

priority_queue pq;

void insert(int element)
{
    pq.size++;
    insert_min_heap(&pq.min_pq, element);
    insert_max_heap(&pq.max_pq, element);
    insert_median_heap(&pq.median_pq, element);
}

int delete_min()
{
    const int deleted_min=delete_min_heap(&pq.min_pq);
    
}

int delete_max()
{
}

int delete_median()
{
}

int find_min()
{
    return find_min_heap(&pq.min_pq);
}

int find_max()
{
    return find_max_heap(&pq.max_pq);
}

int find_median()
{
    return find_median_heap(&pq.median_pq);
}

int main()
{
    // init_pq(&pq);

    // int N = 10;
    // scanf("%d", &N);
    // while (N--)
    // {
    //     fgets(user_input, kUSER_INPUT_SIZE, stdin);
    //     // get user_input
    // }

    return 0;
}