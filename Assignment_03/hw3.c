#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TYPE int
#define BUFFERSIZE 128
#define MAXTOKENZEDSIZE 4
/*
    delete edge 의 경우 tree를 이루는 edge가 delete되면 새로 계산 아닌경우 계산 하지 않음
    change edge 의 경우 바뀐 weight의 값이 tree를 이루는 edge들의 weight의 최댓값 초과 일시 계산X, 최댓값 이하일시 계산 O
    insert edge 의 경우 weight의 값이 tree를 이루는 edge의 weight의 최댓값 초과 계산 X, 최댓값 이하일시 계산 O
*/
typedef struct
{
    int node1;
    int node2;
    int weight;
} edge;

typedef struct
{
    edge *arr;
    int capacity;
    int size;
} vector;

void tokenize_input(char *input, char *tokenized_input[MAXTOKENZEDSIZE + 1])
{
    int size = 0;
    char *ptr = strtok(input, " ");
    while (ptr != NULL)
    {
        tokenized_input[size++];
        strtok(NULL, " ");
    }
    tokenized_input[size] = NULL;
    return;
}

int main()
{
    //open input file
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
    //get input
    char input[BUFFERSIZE];

    fgets(input, BUFFERSIZE, input_fp);

    const int N = atoi(input);

    char *tokenized_input[MAXTOKENZEDSIZE + 1];
    for (int i = 0; i < N; ++i)
    {
        fgets(input, BUFFERSIZE, input_fp);
        printf("%s\n", input);
        tokenize_input(input, tokenized_input);

        if (strcmp(tokenized_input[0], "findMST") == 0)
        {
            findMST();
        }
        else
        {
            edge temp_edge;
            temp_edge.node1 = atoi(tokenized_input[1]);
            temp_edge.node2 = atoi(tokenized_input[2]);
            temp_edge.weight = tokenized_input[3] == NULL ? 0 : atoi(tokenized_input[3]);
            if (strcmp(tokenized_input[0], "deleteEdge") == 0)
            {
                deleteEdge(temp_edge);
            }
            else if (strcmp(tokenized_input[0], "insertEdge") == 0)
            {
                insertEdge(temp_edge);
            }
            else
            {
                changeWeight(temp_edge);
            }
        }
    }

    fclose(input_fp);
    fclose(output_fp);

    return 0;
}
