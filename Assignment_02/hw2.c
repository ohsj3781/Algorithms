#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR 5
#define MAX_STR_LEN 121

#define max(a, b) (((a) > (b)) ? (a) : (b))

char *dp;

typedef struct{
    int idx[MAX_STR];
    int idx_max[MAX_STR];
}idxs;

typedef struct
{
    char data[MAX_STR_LEN];
    int length;
} string;

typedef struct
{
    string data[MAX_STR];
    int n;
} strings;

void find_LCS(const strings user_input, char *ans)
{
    const int N = user_input.n;
    unsigned long long memsize = 1;
    for (int i = user_input.n - 1; i >= 0; --i)
    {
        memsize *= user_input.data[i].length;
    }

    dp = (char *)calloc(memsize, sizeof(char));



    free(dp);
    return;
}

void find_Hirschberg_LCS(const strings user_input, char *ans)
{
    unsigned long long mem_size = 1;
    for (int i = user_input.n; i >= 0; --i)
    {
        mem_size *= user_input.data[i].length;
    }
    return;
}

int main()
{
    FILE *input_file;
    if ((input_file = fopen("hw2_input.txt", "r")) == NULL)
    {
        printf("hw2_input.txt not exist");
        return (-1);
    }

    strings user_input;
    const int number_of_strings = fgetc(input_file) - '0';
    while (fgetc(input_file) != '\n')
    {
    }

    while (fgetc(input_file) != '$')
    {
    }
    while (fgetc(input_file) != '\n')
    {
    }
    for (int i = 0; i < number_of_strings; ++i)
    {
        fgets(user_input.data[i].data, MAX_STR_LEN, input_file);
        user_input.data[i].length = strlen(user_input.data[i].data);
        user_input.data[i].data[user_input.data[i].length - 1] = '\0';
    }
    fclose(input_file);

    char ans[MAX_STR_LEN];

    find_LCS(user_input, ans);
    return 0;
}