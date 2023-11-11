#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR 5
#define MAX_STR_LEN 121

#define max(a, b) (((a) > (b)) ? (a) : (b))

char *dp;

typedef struct
{
    int idx[MAX_STR];
    int idx_max[MAX_STR];
} idxs;

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

void find_LCS2(strings *user_input, char *ans)
{
    char *str1, *str2;
    strcpy(str1, user_input->data[0].data);
    strcpy(str2, user_input->data[1].data);

    const int str1_len = user_input->data[0].length;
    const int str2_len = user_input->data[1].length;

    const int bias_idx_1 = str2_len + 1;
    char *dp = (char *)calloc((str1_len + 1) * (bias_idx_1), sizeof(char));

    // find LCS length
    for (register int idx_1 = 0; idx_1 <= str1_len; ++idx_1)
    {
        for (register int idx_2 = 0; idx_2 <= str2_len; ++idx_2)
        {
            if (idx_1 > 0 && idx_2 > 0 && str1[idx_1 - 1] == str2[idx_2 - 1])
            {
                dp[idx_1 * bias_idx_1 + idx_2] = dp[(idx_1 - 1) * bias_idx_1 + (idx_2 - 1)] + 1;
            }
            else
            {
                dp[idx_1 * bias_idx_1 + idx_2] = max(dp[(idx_1 - 1) * bias_idx_1 + (idx_2)], dp[(idx_1)*bias_idx_1 + (idx_2 - 1)]);
            }
        }
    }

    // backtracking LCS
    int ans_idx = dp[str1_len * bias_idx_1 + str2_len];
    ans[ans_idx] = '\0';
    register int idx_1 = str1_len;
    register int idx_2 = str2_len;

    while (dp[idx_1 * bias_idx_1 + idx_2] != 0)
    {
        if (dp[(idx_1 - 1) * bias_idx_1 + (idx_2)] == dp[idx_1 * bias_idx_1 + idx_2])
        {
            --idx_1;
        }
        else if (dp[(idx_1)*bias_idx_1 + (idx_2 - 1)] == dp[idx_1 * bias_idx_1 + idx_2])
        {
            --idx_2;
        }
        else
        {
            ans[--ans_idx] = str1[idx_1 - 1];
        }
    }

    free(dp);

    return;
}

void find_LCS5(strings *user_input, char *ans)
{
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

    find_LCS(&user_input, ans);
    return 0;
}