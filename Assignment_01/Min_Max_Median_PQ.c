#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define kUSER_INPUT_SIZE 64

static char user_input[kUSER_INPUT_SIZE];

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

void init_heap(heap *min_heap_ptr, const int N)
{
    min_heap_ptr->size = 0;
    min_heap_ptr->valid_size = 0;
    min_heap_ptr->array = (int *)calloc(N, sizeof(int));
    return;
}

typedef struct
{
    int size;
    int valid_size;
    heap left_max_heap;
    heap right_min_heap;
} median_heap;

void init_median_heap(median_heap *median_heap_ptr, const int N)
{
    median_heap_ptr->size = 0;
    median_heap_ptr->valid_size = 0;
    init_heap(&median_heap_ptr->left_max_heap, N);
    init_heap(&median_heap_ptr->right_min_heap, N);
    return;
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
    // init_median_heap(&pq_ptr->median_pq, N);
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
        swap(&heap_arr[now_idx], &heap_arr[parent_idx]);
        now_idx = parent_idx;
        parent_idx = (now_idx - 1) / 2;
    }
    return;
}

const int delete_heap(heap *heap_ptr, const int (*compare)(const data now, const data parent))
{
    if (heap_ptr->valid_size <= 0)
    {
        return -1;
    }
    int *heap_size = &heap_ptr->size;
    int *heap_valid_size = &heap_ptr->valid_size;
    int *heap_arr = heap_ptr->array;
    data *data_arr = pq.data_array;

    int valid_data_shown = 0;
    int deleted_value = 0;

    while (*heap_size > 0 && *heap_valid_size > 0)
    {
        if (data_arr[heap_arr[0]].deleted == 0)
        {
            if (++valid_data_shown >= 2)
            {
                break;
            }
        }
        // if second valid data shown break delete datas
        swap(&heap_arr[0], &heap_arr[*heap_size - 1]);
        (*heap_size)--;

        if (data_arr[heap_arr[*heap_size]].deleted == 0)
        {
            deleted_value = data_arr[heap_arr[*heap_size]].value;
            data_arr[heap_arr[*heap_size]].deleted++;
            (*heap_valid_size)--;
        }
        // valid data

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
    return deleted_value;
}

const int find_heap(heap *heap_ptr)
{
    return pq.data_array[heap_ptr->array[0]].value;
}

void insert(int element)
{
    pq.data_array[pq.size].value = element;
    pq.data_array[pq.size].deleted = 0;
    pq.size++;
    insert_heap(&pq.min_pq, pq.size - 1, compare_min_heap);
    insert_heap(&pq.max_pq, pq.size - 1, compare_max_heap);
    // insert_median_heap(&pq.median_pq, pq.size-1);
}

int delete_min()
{
    return delete_heap(&pq.min_pq, compare_min_heap);
}

int delete_max()
{
    return delete_heap(&pq.max_pq, compare_max_heap);
}

int delete_median()
{
    return 0;
}

int find_min()
{
    return find_heap(&pq.min_pq);
}

int find_max()
{
    return find_heap(&pq.max_pq);
}

int find_median()
{
    // return find_median_heap(&pq.median_pq);
    return 0;
}

int main()
{

    // int N;
    // scanf("%d", &N);

    // while (N--)
    // {
    //     fgets(user_input, kUSER_INPUT_SIZE, stdin);
    //     // get user_input
    // }

    int input[] = {1, 3, 5, 7, 9, 2, 4, 6, 8, 10};
    const int N = sizeof(input) / sizeof(int);
    init_pq(&pq, N);

    for (int i = 0; i < sizeof(input) / sizeof(int); ++i)
    {
        insert(input[i]);
        // for(int j=0;j<=i;++j){
        //     printf("{%d ,%d} ",pq.data_array[pq.min_pq.array[j]].value,pq.data_array[pq.min_pq.array[j]].deleted);
        // }
        printf("\n");
    }

    // for(int i=0;i<N;++i){
    //     printf("%d %d\n",pq.data_array[i].value,pq.data_array[i].deleted);
    // }

    for (int i = 0; i < N / 2; ++i)
    {

        printf("%d\n", delete_max());
        printf("%d\n", delete_min());
    }

    printf("\n");

    return 0;
}