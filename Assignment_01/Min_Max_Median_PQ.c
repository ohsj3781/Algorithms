#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define kUSER_INPUT_SIZE 64

typedef struct
{
    int value;
    int deleted;
} data;

const int compare_min_heap(const data now, const data other)
{
    return now.value < other.value ? 1 : 0;
}

const int compare_max_heap(const data now, const data other)
{
    return now.value > other.value ? 1 : 0;
}

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
    int valid_size;
    int *array;
} heap;

void init_heap(heap *heap_ptr, const int N)
{
    heap_ptr->size = 0;
    heap_ptr->valid_size = 0;
    heap_ptr->array = (int *)calloc(N, sizeof(int));
    return;
}

void free_heap(heap *heap_ptr)
{
    free(heap_ptr->array);
}

typedef struct
{
    int valid_size;
    heap left_max_heap;
    heap right_min_heap;
} median_heap;

void init_median_heap(median_heap *median_heap_ptr, const int N)
{
    median_heap_ptr->valid_size = 0;
    init_heap(&median_heap_ptr->left_max_heap, N);
    init_heap(&median_heap_ptr->right_min_heap, N);
    return;
}

void free_median_heap(median_heap *median_heap_ptr)
{
    free_heap(&median_heap_ptr->left_max_heap);
    free_heap(&median_heap_ptr->right_min_heap);
}

typedef struct
{
    int size;
    data *data_array;
    heap min_pq;
    heap max_pq;
    median_heap median_pq;
} priority_queue;

priority_queue pq;

void init_pq(priority_queue *pq_ptr, const int N)
{
    pq_ptr->size = 0;
    pq_ptr->data_array = (data *)calloc(N, sizeof(data));
    init_heap(&pq_ptr->min_pq, N);
    init_heap(&pq_ptr->max_pq, N);
    init_median_heap(&pq_ptr->median_pq, N);
}

void free_pq(priority_queue *pq_ptr)
{
    free_heap(&pq_ptr->min_pq);
    free_heap(&pq_ptr->max_pq);
    free_median_heap(&pq_ptr->median_pq);
}

void heapify(heap *heap_ptr, const int (*compare)(const data now, const data parent))
{
    int *heap_size = &heap_ptr->size;
    int *heap_arr = heap_ptr->array;
    data *data_arr = pq.data_array;
    int now_idx = 0;
    int left_child_idx = 2 * now_idx + 1;
    int right_child_idx = 2 * now_idx + 2;
    int compare_idx;

    while (left_child_idx < *heap_size)
    {
        if (right_child_idx < *heap_size)
        {
            compare_idx = compare(data_arr[heap_arr[left_child_idx]], data_arr[heap_arr[right_child_idx]]) ? left_child_idx : right_child_idx;
        }
        else
        {
            compare_idx = left_child_idx;
        }
        if (compare(data_arr[heap_arr[now_idx]], data_arr[heap_arr[compare_idx]]))
        {
            break;
        }
        swap(&heap_arr[now_idx], &heap_arr[compare_idx]);
        now_idx = compare_idx;
        left_child_idx = 2 * now_idx + 1;
        right_child_idx = 2 * now_idx + 2;
    }
}

void delete_unvaild_data_heap(heap *heap_ptr, const int (*compare)(const data now, const data parent))
{
    int *heap_size = &heap_ptr->size;
    int *heap_valid_size = &heap_ptr->valid_size;
    int *heap_arr = heap_ptr->array;
    data *data_arr = pq.data_array;

    while (*heap_size > 0 && *heap_valid_size > 0 && data_arr[heap_arr[0]].deleted > 0)
    {
        // if second valid data shown break delete datas
        swap(&heap_arr[0], &heap_arr[*heap_size - 1]);
        (*heap_size)--;
        heapify(heap_ptr, compare);
    }
    return;
}

void insert_heap(heap *heap_ptr, const int element_idx, const int (*compare)(const data now, const data parent))
{
    int *heap_size = &heap_ptr->size;
    int *heap_valid_size = &heap_ptr->valid_size;
    int *heap_arr = heap_ptr->array;

    heap_arr[*heap_size] = element_idx;
    (*heap_size)++;
    (*heap_valid_size)++;

    int now_idx = *heap_size - 1;
    int parent_idx = (now_idx - 1) / 2;

    while (now_idx > 0 && compare(pq.data_array[heap_arr[now_idx]], pq.data_array[heap_arr[parent_idx]]))
    {
        data now = pq.data_array[heap_arr[now_idx]];
        data parent = pq.data_array[heap_arr[parent_idx]];
        swap(&heap_arr[now_idx], &heap_arr[parent_idx]);
        now_idx = parent_idx;
        parent_idx = (now_idx - 1) / 2;
    }
    delete_unvaild_data_heap(heap_ptr, compare);
    return;
}

data *delete_heap(heap *heap_ptr, const int (*compare)(const data now, const data parent))
{
    int *heap_size = &heap_ptr->size;
    int *heap_valid_size = &heap_ptr->valid_size;
    int *heap_arr = heap_ptr->array;
    data *data_arr = pq.data_array;

    data *deleted_data_ptr = NULL;

    delete_unvaild_data_heap(heap_ptr, compare);

    swap(&heap_arr[0], &heap_arr[*heap_size - 1]);
    (*heap_size)--;
    (*heap_valid_size)--;
    deleted_data_ptr = &data_arr[heap_arr[*heap_size]];
    heapify(heap_ptr, compare);

    delete_unvaild_data_heap(heap_ptr, compare);

    return deleted_data_ptr;
}

data *find_heap(heap *heap_ptr, const int (*compare)(const data now, const data parent))
{
    delete_unvaild_data_heap(heap_ptr, compare);
    return &pq.data_array[heap_ptr->array[0]];
}

void balance_median_heap(median_heap *heap_ptr)
{
    while (heap_ptr->left_max_heap.valid_size > heap_ptr->right_min_heap.valid_size + 1)
    {
        data *moved_data = delete_heap(&heap_ptr->left_max_heap, compare_max_heap);
        insert_heap(&heap_ptr->right_min_heap, moved_data - pq.data_array, compare_min_heap);
    }
    // move data left to right

    while (heap_ptr->left_max_heap.valid_size < heap_ptr->right_min_heap.valid_size)
    {
        data *moved_data = delete_heap(&heap_ptr->right_min_heap, compare_min_heap);
        insert_heap(&heap_ptr->left_max_heap, moved_data - pq.data_array, compare_max_heap);
    }
    // move data right to left
}

void insert_median_heap(median_heap *heap_ptr, const int element_idx)
{
    int *heap_valid_size = &heap_ptr->valid_size;

    if ((*heap_valid_size)++ == 0)
    {
        insert_heap(&heap_ptr->left_max_heap, element_idx, compare_max_heap);
        return;
    }

    balance_median_heap(heap_ptr);

    const int pivot = find_heap(&heap_ptr->left_max_heap, compare_max_heap)->value;

    if (pq.data_array[element_idx].value < pivot)
    {
        insert_heap(&heap_ptr->left_max_heap, element_idx, compare_max_heap);
    }
    else
    {
        insert_heap(&heap_ptr->right_min_heap, element_idx, compare_min_heap);
    }

    balance_median_heap(heap_ptr);
}

data *delete_median_heap(median_heap *heap_ptr)
{
    int *heap_valid_size = &heap_ptr->valid_size;

    balance_median_heap(heap_ptr);

    data *deleted_data = delete_heap(&heap_ptr->left_max_heap, compare_max_heap);

    (*heap_valid_size)--;

    balance_median_heap(heap_ptr);
    return deleted_data;
}

data *find_median_heap(median_heap *heap_ptr)
{
    balance_median_heap(heap_ptr);
    return find_heap(&heap_ptr->left_max_heap, compare_max_heap);
}

void insert(int element)
{
    pq.data_array[pq.size].value = element;
    pq.data_array[pq.size].deleted = 0;
    pq.size++;
    insert_heap(&pq.min_pq, pq.size - 1, compare_min_heap);
    insert_heap(&pq.max_pq, pq.size - 1, compare_max_heap);
    insert_median_heap(&pq.median_pq, pq.size - 1);
}

int delete_min()
{
    if (pq.size <= 0)
    {
        return 0;
    }
    data *delete_data_ptr = delete_heap(&pq.min_pq, compare_min_heap);
    delete_data_ptr->deleted++;
    if (--pq.size == 0)
    {
        pq.min_pq.size = 0;
        pq.min_pq.valid_size = 0;
        pq.max_pq.size = 0;
        pq.max_pq.valid_size = 0;
        pq.median_pq.left_max_heap.size = 0;
        pq.median_pq.left_max_heap.valid_size = 0;
        pq.median_pq.right_min_heap.size = 0;
        pq.median_pq.right_min_heap.valid_size = 0;
        pq.median_pq.valid_size = 0;
    }
    else
    {
        pq.max_pq.valid_size--;
        pq.median_pq.left_max_heap.valid_size--;
    }
    return delete_data_ptr->value;
}

int delete_max()
{
    if (pq.size <= 0)
    {
        return 0;
    }
    data *delete_data_ptr = delete_heap(&pq.max_pq, compare_max_heap);
    delete_data_ptr->deleted++;
    if (--pq.size == 0)
    {
        pq.min_pq.size = 0;
        pq.min_pq.valid_size = 0;
        pq.max_pq.size = 0;
        pq.max_pq.valid_size = 0;
        pq.median_pq.left_max_heap.size = 0;
        pq.median_pq.left_max_heap.valid_size = 0;
        pq.median_pq.right_min_heap.size = 0;
        pq.median_pq.right_min_heap.valid_size = 0;
        pq.median_pq.valid_size = 0;
    }
    else
    {
        pq.max_pq.valid_size--;
        pq.median_pq.left_max_heap.valid_size--;
    }
    return delete_data_ptr->value;
}

int delete_median()
{
    if (pq.size <= 0)
    {
        return 0;
    }
    data *deleted_data_ptr = delete_median_heap(&pq.median_pq);
    deleted_data_ptr->deleted++;
    if (--pq.size == 0)
    {
        pq.min_pq.size = 0;
        pq.min_pq.valid_size = 0;
        pq.max_pq.size = 0;
        pq.max_pq.valid_size = 0;
        pq.median_pq.left_max_heap.size = 0;
        pq.median_pq.left_max_heap.valid_size = 0;
        pq.median_pq.right_min_heap.size = 0;
        pq.median_pq.right_min_heap.valid_size = 0;
        pq.median_pq.valid_size = 0;
    }
    else
    {
        pq.max_pq.valid_size--;
        pq.median_pq.left_max_heap.valid_size--;
    }

    return deleted_data_ptr->value;
}

int find_min()
{
    data *find_data_ptr = find_heap(&pq.min_pq, compare_min_heap);
    return find_data_ptr->value;
}

int find_max()
{
    data *find_data_ptr = find_heap(&pq.max_pq, compare_max_heap);
    return find_data_ptr->value;
}

int find_median()
{
    data *find_data_ptr = find_median_heap(&pq.median_pq);
    return find_data_ptr->value;
}

int main()
{
    char user_input[kUSER_INPUT_SIZE];

    int N;
    scanf("%d", &N);
    while (getchar() != '\n')
    {
    }
    init_pq(&pq, N);
    while (N--)
    {
        fgets(user_input, kUSER_INPUT_SIZE, stdin);
        // get user_input
        if (user_input[0] == 'I')
        {
            const int element = atoi(user_input + 2);
            insert(element);
        }
        // insert element
        else if (user_input[0] == 'D')
        {
            if (pq.size <= 0)
            {
                break;
            }
            const char choice = user_input[2];
            int deleted_value = 0;
            if (choice == 'M')
            {
                deleted_value = delete_min();
            }
            else if (choice == 'X')
            {
                deleted_value = delete_max();
            }
            else
            {
                deleted_value = delete_median();
            }
        }
        // delete
        else
        {
            if (pq.size <= 0)
            {
                printf("NULL\n");
                continue;
            }
            const char choice = user_input[2];
            int find_value = 0;
            if (choice == 'M')
            {
                find_value = find_min();
            }
            else if (choice == 'X')
            {
                find_value = find_max();
            }
            else
            {
                find_value = find_median();
            }
            printf("%d\n", find_value);
        }
        // user_input[0]=='F' find
    }

    free_pq(&pq);
    return 0;
}