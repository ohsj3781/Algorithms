#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TYPE int
#define BUFFERSIZE 128
#define MAXTOKENZEDSIZE 4

typedef struct
{
    int node1;
    int node2;
} edge;

typedef struct
{
    edge *arr;
    int capacity;
    int size;
} heap;

typedef struct
{
    int *nodes;
    int capacity;
    int size;
} set;

heap h;
set *set_arr;
int *nodes_set;
// number of nodes
int N;
int need_to_calc_MST = 1;
// 0 is not exist, 1 is in MST, 2 is not in MST
int **edge_mark;
int **edge_weight;
/*
    delete edge 의 경우 tree를 이루는 edge가 delete되면 새로 계산 아닌경우 계산 하지 않음
    change edge 의 경우 바뀐 weight의 값이 tree를 이루는 edge들의 weight의 최댓값 초과 일시 계산X, 최댓값 이하일시 계산 O
    insert edge 의 경우 weight의 값이 tree를 이루는 edge의 weight의 최댓값 초과 계산 X, 최댓값 이하일시 계산 O
*/

// edge function
void swap_edge(edge *le, edge *re)
{
    const edge temp = *le;
    *le = *re;
    *re = temp;
    return;
}

// heap function

void init_heap()
{
    h.size = 0;
    h.capacity = 16;
    h.arr = (edge *)calloc(h.capacity, sizeof(edge));
}

const int compare(const edge e1, const edge e2)
{
    return edge_weight[e1.node1][e1.node2] < edge_weight[e2.node1][e2.node2] ? 1 : 0;
}

void heapify(int idx)
{
    const int h_size = h.size;
    int left_child_idx = 2 * idx + 1;
    int right_child_idx = left_child_idx + 1;
    int compare_idx;
    while (left_child_idx < h_size)
    {
        if (right_child_idx < h_size)
        {
            compare_idx = compare(h.arr[left_child_idx], h.arr[right_child_idx]) ? left_child_idx : right_child_idx;
        }
        else
        {
            compare_idx = left_child_idx;
        }

        if (compare(h.arr[idx], h.arr[compare_idx]))
        {
            break;
        }
        swap_edge(&h.arr[idx], &h.arr[compare_idx]);
        idx = compare_idx;
        left_child_idx = 2 * idx + 1;
        right_child_idx = left_child_idx + 1;
    }
}

void insert_heap(edge e)
{
    if (h.size == h.capacity)
    {
        h.capacity *= 2;
        h.arr = (edge *)realloc(h.arr, h.capacity * sizeof(edge));
    }
    h.arr[h.size++] = e;

    int now_idx = h.size - 1;
    int parent_idx = (now_idx - 1) >> 1;

    while (now_idx > 0 && compare(h.arr[now_idx], h.arr[parent_idx]))
    {
        swap_edge(&h.arr[now_idx], &h.arr[parent_idx]);
        now_idx = parent_idx;
        parent_idx = (now_idx - 1) >> 1;
    }
}

const edge pop_heap()
{
    --h.size;
    swap_edge(&h.arr[0], &h.arr[h.size]);
    heapify(0);
    return h.arr[h.size];
}

void free_heap()
{
    free(h.arr);
}

// set function
void init_set(set *s_ptr)
{
    s_ptr->capacity = 1;
    s_ptr->size = 0;
    s_ptr->nodes = (int *)calloc(s_ptr->capacity, sizeof(int));
    return;
}

void push_set(set *s_ptr, const int node)
{
    if (s_ptr->size == s_ptr->capacity)
    {
        s_ptr->capacity *= 2;
        s_ptr->nodes = (int *)realloc(s_ptr->nodes, sizeof(int) * s_ptr->capacity);
    }
    s_ptr->nodes[s_ptr->size++] = node;
    nodes_set[node] = s_ptr - set_arr;
    return;
}

void reset_set(set *s_ptr)
{
    s_ptr->size = 0;
    return;
}

void union_set(set *ls, set *rs)
{
    set *bigger_set;
    set *smaller_set;
    if (ls->size > rs->size)
    {
        bigger_set = ls;
        smaller_set = rs;
    }
    else
    {
        bigger_set = rs;
        smaller_set = ls;
    }

    const int smaller_set_size = smaller_set->size;
    for (int i = 0; i < smaller_set_size; ++i)
    {
        push_set(bigger_set, smaller_set->nodes[i]);
    }
    reset_set(smaller_set);
    return;
}

void free_set(set *s)
{
    free(s->nodes);
}

// main function
void insertEdge(edge e, const int weight)
{
    if (e.node1 > e.node2)
    {
        const int temp = e.node1;
        e.node1 = e.node2;
        e.node2 = temp;
    }
    // if edge is already exist ignore
    if (edge_mark[e.node1][e.node2] != 0)
    {
        return;
    }

    edge_mark[e.node1][e.node2] = 2;
    edge_weight[e.node1][e.node2] = weight;

    insert_heap(e);
    return;
}

void deleteEdge(const edge e)
{
    if (edge_mark[e.node1][e.node2] == 0)
    {
        return;
    }
    edge_mark[e.node1][e.node2] = 0;
    int idx = 0;
    for (idx; idx < h.size; ++idx)
    {
        if (h.arr[idx].node1 == e.node1 && h.arr[idx].node2 == e.node2)
        {
            break;
        }
    }
    --h.size;
    swap_edge(&h.arr[idx], &h.arr[h.size]);
    heapify(idx);
}

void changeWeight(const edge e, const int weight)
{
    if (edge_mark[e.node1][e.node2] == 0)
    {
        return;
    }
    edge_weight[e.node1][e.node2] = weight;
    int idx = 0;
    for (idx; idx < h.size; ++idx)
    {
        if (h.arr[idx].node1 == e.node1 && h.arr[idx].node2 == e.node2)
        {
            break;
        }
    }

    heapify(idx);
}

const int findMST()
{
    static int MST_weight_sum = 0;
    if (h.size < N - 1)
    {
        return -1;
    }
    if (!need_to_calc_MST)
    {
        return MST_weight_sum;
    }
    MST_weight_sum = 0;
    // reset nodes_set;
    for (int i = 1; i < N + 1; ++i)
    {
        reset_set(&set_arr[i]);
        push_set(&set_arr[i], i);
    }
    int poped_edges = 0;
    int number_of_mst_edges = 0;
    while (h.size > 0 && number_of_mst_edges < N && h.size >= N - 1 - number_of_mst_edges)
    {
        const edge now_edge = pop_heap();
        ++poped_edges;
        if (nodes_set[now_edge.node1] == nodes_set[now_edge.node2])
        {
            continue;
        }
        MST_weight_sum += edge_weight[now_edge.node1][now_edge.node2];
        number_of_mst_edges++;
        union_set(&set_arr[nodes_set[now_edge.node1]], &set_arr[nodes_set[now_edge.node2]]);
    }

    int return_value = MST_weight_sum;

    for (int i = 2; i <= N; ++i)
    {

        if (nodes_set[i] != nodes_set[i - 1])
        {
            return_value = -1;
            break;
        }
    }

    h.size += poped_edges;
    for (int i = h.size - 1; i >= 0; --i)
    {
        heapify(i);
    }

    return return_value;
}
void tokenize_input(char *input, char *tokenized_input[MAXTOKENZEDSIZE + 1])
{
    int size = 0;
    char *ptr = strtok(input, " ");
    while (ptr != NULL)
    {
        tokenized_input[size++] = ptr;
        ptr[strlen(ptr)] = '\0';
        ptr = strtok(NULL, " ");
    }
    tokenized_input[size] = NULL;
    return;
}

int main()
{
    // open input file
    char *input_file_name = "mst.in";
    char *output_file_name = "mst.out";

    FILE *input_fp, *output_fp;

    if ((input_fp = fopen(input_file_name, "r")) == NULL)
    {
        fprintf(stderr, "%s doesn't exist\n", input_file_name);
        return -1;
    }

    if ((output_fp = fopen(output_file_name, "w")) == NULL)
    {
        fprintf(stderr, "fail to open %s\n", output_file_name);
        return -1;
    }
    // get input
    char input[BUFFERSIZE];

    fgets(input, BUFFERSIZE, input_fp);

    N = atoi(input);
    char *tokenized_input[MAXTOKENZEDSIZE + 1];

    // alloc edge_mark, edge_weight, set_arr, nodes_set;
    edge_mark = (int **)calloc(N + 1, sizeof(int *));
    for (int i = 0; i < N + 1; ++i)
    {
        edge_mark[i] = calloc(N + 1, sizeof(int));
    }

    edge_weight = (int **)calloc(N + 1, sizeof(int *));
    for (int i = 0; i < N + 1; ++i)
    {
        edge_weight[i] = calloc(N + 1, sizeof(int));
    }

    set_arr = (set *)calloc(N + 1, sizeof(set));
    for (int i = 0; i < N + 1; ++i)
    {
        init_set(&set_arr[i]);
    }

    nodes_set = (int *)calloc(N + 1, sizeof(int));

    init_heap();

    char output[BUFFERSIZE];
    // calculate
    while (fgets(input, BUFFERSIZE, input_fp) != NULL)
    {
        tokenize_input(input, tokenized_input);

        if (strncmp(tokenized_input[0], "findMST", 7) == 0)
        {
            const int MST_wegiht = findMST();
            if (MST_wegiht == -1)
            {
                strcpy(output, "Disconnected\n");
                fwrite(output, sizeof(char), strlen(output), output_fp);
            }
            else
            {
                sprintf(output, "%d\n", MST_wegiht);
                fwrite(output, sizeof(char), strlen(output), output_fp);
            }
        }
        else
        {
            edge temp_edge;
            temp_edge.node1 = atoi(tokenized_input[1]);
            temp_edge.node2 = atoi(tokenized_input[2]);
            if (strncmp(tokenized_input[0], "deleteEdge", 10) == 0)
            {
                deleteEdge(temp_edge);
                continue;
            }
            const int temp_weight = atoi(tokenized_input[3]);
            if (strcmp(tokenized_input[0], "insertEdge") == 0)
            {
                insertEdge(temp_edge, temp_weight);
            }
            else
            {
                changeWeight(temp_edge, temp_weight);
            }
        }
    }

    // free vector,edge_mark,edge_weight, set_arr, nodes_set and  file points

    for (int i = 0; i < N + 1; ++i)
    {
        free(edge_mark[i]);
    }
    free(edge_mark);

    for (int i = 0; i < N + 1; ++i)
    {
        free(edge_weight[i]);
    }
    free(edge_weight);

    for (int i = 0; i < N + 1; ++i)
    {
        free_set(&set_arr[i]);
    }
    free(set_arr);

    free(nodes_set);

    free_heap();
    fclose(input_fp);
    fclose(output_fp);

    return 0;
}
