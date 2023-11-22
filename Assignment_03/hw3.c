#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TYPE int
#define BUFFERSIZE 128
#define MAXTOKENZEDSIZE 4

char **matrix;

void insertEdge(const TYPE node1, const TYPE node2, const TYPE weight)
{
    if (matrix[node1][node2] != 0)
    {
        return;
    }
    matrix[node1][node2] = matrix[node2][node1] = weight;
}

const TYPE findMST() {}

void deleteEdge(const TYPE node1, const TYPE node2)
{
    matrix[node1][node2] = matrix[node2][node1] = 0;
    return;
}

void changeWeight(const TYPE node1, const TYPE node2, const TYPE weight)
{
    if (matrix[node1][node2] == 0)
    {
        return;
    }
    matrix[node1][node2] = matrix[node2][node1] = weight;
    return;
}

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

    char input[BUFFERSIZE];

    fgets(input, BUFFERSIZE, input_fp);

    const int N = atoi(input);
    matrix = (char **)calloc(N + 1, sizeof(char *));
    for (int i = 0; i < N + 1; ++i)
    {
        matrix[i] = (char *)calloc(N + 1, sizeof(char));
    }

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
            TYPE node1, node2, weight;
            node1 = atoi(tokenized_input[1]);
            node2 = atoi(tokenized_input[2]);
            if (strcmp(tokenized_input[0], "deleteEdge") == 0)
            {
                deleteEdge(node1, node2);
                continue;
            }
            weight = atoi(tokenized_input[3]);
            if (strcmp(tokenized_input[0], "insertEdge") == 0)
            {
                insertEdge(node1, node2, weight);
            }
            else
            {
                changeWeight(node1, node2, weight);
            }
        }
    }

    for (int i = 0; i < N + 1; ++i)
    {
        free(matrix[i]);
    }
    free(matrix);

    fclose(input_fp);
    fclose(output_fp);

    return 0;
}
