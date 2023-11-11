#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR 5
#define MAX_STR_LEN 121

#define max(a, b) (((a) > (b)) ? (a) : (b))

char *dp;



typedef struct
{
    char data[MAX_STR_LEN];
    int len;
} string;

void find_LCS2(string *str1, string *str2, string *ans)
{
    // alloc dp
    char **dp = (char **)calloc(str1->len + 1, sizeof(char *));
    for (int i = 0; i <= str1->len; ++i)
    {
        dp[i] = (char *)calloc(str2->len + 1, sizeof(char));
    }

    // find LCS length
    for (register int idx_1 = 1; idx_1 <= str1->len; ++idx_1)
    {
        for (register int idx_2 = 1; idx_2 <= str2->len; ++idx_2)
        {
            if (str1->data[idx_1 - 1] == str2->data[idx_2 - 1])
            {
                dp[idx_1][idx_2] = dp[idx_1 - 1][idx_2 - 1] + 1;
            }
            else
            {
                dp[idx_1][idx_2] = max(dp[idx_1 - 1][idx_2], dp[idx_1][idx_2 - 1]);
            }
        }
    }

    // backtracking LCS
    int ans_idx = dp[str1->len][str2->len];
    ans->data[ans_idx] = '\0';
    ans->len=ans_idx;
    register int idx_1 = str1->len;
    register int idx_2 = str2->len;

    while (dp[idx_1][idx_2] != 0)
    {
        if (dp[idx_1 - 1][idx_2] == dp[idx_1][idx_2])
        {
            --idx_1;
        }
        else if (dp[idx_1][idx_2 - 1] == dp[idx_1][idx_2])
        {
            --idx_2;
        }
        else
        {
            ans->data[--ans_idx] = str1->data[idx_1 - 1];
            --idx_1;
            --idx_2;
        }
    }

    for (int i = 0; i < str1->len + 1; ++i)
    {
        free(dp[i]);
    }
    free(dp);

    return;
}

void find_LCS3(string *str1, string *str2, string *str3, string *ans)
{
    // alloc dp
    char ***dp = (char ***)calloc(str1->len + 1, sizeof(char **));

    for (int i = 0; i <= str1->len; ++i)
    {
        dp[i] = (char **)calloc(str2->len + 1, sizeof(char *));
        for (int j = 0; j <= str2->len; ++j)
        {
            dp[i][j] = (char *)calloc(str3->len + 1, sizeof(char));
        }
    }

    // find LCS length
    for (register int idx_1 = 1; idx_1 <= str1->len; ++idx_1)
    {
        for (register int idx_2 = 1; idx_2 <= str2->len; ++idx_2)
        {
            for (register int idx_3 = 1; idx_3 <= str3->len; ++idx_3)
            {

                if (str1->data[idx_1 - 1] == str2->data[idx_2 - 1] && str1->data[idx_1 - 1] == str3->data[idx_3 - 1])
                {
                    dp[idx_1][idx_2][idx_3] = dp[idx_1 - 1][idx_2 - 1][idx_3 - 1] + 1;
                }
                else
                {
                    dp[idx_1][idx_2][idx_3] = max(dp[idx_1 - 1][idx_2][idx_3], max(dp[idx_1][idx_2 - 1][idx_3], dp[idx_1][idx_2][idx_3 - 1]));
                }
            }
        }
    }

    // backtracking LCS
    int ans_idx = dp[str1->len][str2->len][str3->len];
    ans->data[ans_idx] = '\0';
    ans->len=ans_idx;
    register int idx_1 = str1->len;
    register int idx_2 = str2->len;
    register int idx_3 = str3->len;

    while (dp[idx_1][idx_2][idx_3] != 0)
    {

        if (dp[idx_1 - 1][idx_2][idx_3] == dp[idx_1][idx_2][idx_3])
        {
            --idx_1;
        }
        else if (dp[idx_1][idx_2 - 1][idx_3] == dp[idx_1][idx_2][idx_3])
        {
            --idx_2;
        }
        else if (dp[idx_1][idx_2][idx_3 - 1] == dp[idx_1][idx_2][idx_3])
        {
            --idx_3;
        }
        else
        {
            ans->data[--ans_idx] = str1->data[idx_1 - 1];
            --idx_1;
            --idx_2;
            --idx_3;
        }
    }

    // dealloc dp
    for (int i = 0; i <= str1->len; ++i)
    {
        for (int j = 0; j <= str2->len; ++j)
        {
            free(dp[i][j]);
        }
        free(dp[i]);
    }
    free(dp);

    return;
}

void find_LCS4(string *str1, string *str2, string *str3, string *str4, string *ans)
{
    // alloc dp
    char ****dp = (char ****)calloc(str1->len + 1, sizeof(char ***));

    for (int i = 0; i <= str1->len; ++i)
    {
        dp[i] = (char ***)calloc(str2->len + 1, sizeof(char **));
        for (int j = 0; j <= str2->len; ++j)
        {
            dp[i][j] = (char **)calloc(str3->len + 1, sizeof(char *));
            for (int k = 0; k <= str3->len; ++k)
            {
                dp[i][j][k] = (char *)calloc(str4->len + 1, sizeof(char));
            }
        }
    }

    // find LCS length
    for (register int idx_1 = 1; idx_1 <= str1->len; ++idx_1)
    {
        for (register int idx_2 = 1; idx_2 <= str2->len; ++idx_2)
        {
            for (register int idx_3 = 1; idx_3 <= str3->len; ++idx_3)
            {
                for (register int idx_4 = 1; idx_4 <= str4->len; ++idx_4)
                {
                    if (str1->data[idx_1 - 1] == str2->data[idx_2 - 1] && str1->data[idx_1 - 1] == str3->data[idx_3 - 1] && str1->data[idx_1 - 1] == str4->data[idx_4 - 1])
                    {
                        dp[idx_1][idx_2][idx_3][idx_4] = dp[idx_1 - 1][idx_2 - 1][idx_3 - 1][idx_4 - 1] + 1;
                    }
                    else
                    {
                        dp[idx_1][idx_2][idx_3][idx_4] = max(dp[idx_1 - 1][idx_2][idx_3][idx_4], max(dp[idx_1][idx_2 - 1][idx_3][idx_4], max(dp[idx_1][idx_2][idx_3 - 1][idx_4], dp[idx_1][idx_2][idx_3][idx_4 - 1])));
                    }
                }
            }
        }
    }

    // backtracking LCS
    int ans_idx = dp[str1->len][str2->len][str3->len][str4->len];
    ans->data[ans_idx] = '\0';
    ans->len=ans_idx;
    register int idx_1 = str1->len;
    register int idx_2 = str2->len;
    register int idx_3 = str3->len;
    register int idx_4 = str4->len;

    while (dp[idx_1][idx_2][idx_3][idx_4] != 0)
    {

        if (dp[idx_1 - 1][idx_2][idx_3][idx_4] == dp[idx_1][idx_2][idx_3][idx_4])
        {
            --idx_1;
        }
        else if (dp[idx_1][idx_2 - 1][idx_3][idx_4] == dp[idx_1][idx_2][idx_3][idx_4])
        {
            --idx_2;
        }
        else if (dp[idx_1][idx_2][idx_3 - 1][idx_4] == dp[idx_1][idx_2][idx_3][idx_4])
        {
            --idx_3;
        }
        else if (dp[idx_1][idx_2][idx_3][idx_4 - 1] == dp[idx_1][idx_2][idx_3][idx_4])
        {
            --idx_4;
        }
        else
        {
            ans->data[--ans_idx] = str1->data[idx_1 - 1];
            --idx_1;
            --idx_2;
            --idx_3;
            --idx_4;
        }
    }

    // dealloc dp
    for (int i = 0; i <= str1->len; ++i)
    {
        for (int j = 0; j <= str2->len; ++j)
        {
            for (int k = 0; k <= str3->len; ++k)
            {
                free(dp[i][j][k]);
            }
            free(dp[i][j]);
        }
        free(dp[i]);
    }
    free(dp);

    return;
}

void find_LCS5(string *str1, string *str2, string *str3, string *str4, string *str5, string *ans)
{
    // alloc dp
    char *****dp = (char *****)calloc(str1->len + 1, sizeof(char ****));

    for (int i = 0; i <= str1->len; ++i)
    {
        dp[i] = (char ****)calloc(str2->len + 1, sizeof(char ***));
        for (int j = 0; j <= str2->len; ++j)
        {
            dp[i][j] = (char ***)calloc(str3->len + 1, sizeof(char **));
            for (int k = 0; k <= str3->len; ++k)
            {
                dp[i][j][k] = (char **)calloc(str4->len + 1, sizeof(char *));
                for (int l = 0; l <= str4->len; ++l)
                {
                    dp[i][j][k][l] = (char *)calloc(str5->len + 1, sizeof(char));
                }
            }
        }
    }

    // find LCS length
    for (register int idx_1 = 1; idx_1 <= str1->len; ++idx_1)
    {
        for (register int idx_2 = 1; idx_2 <= str2->len; ++idx_2)
        {
            for (register int idx_3 = 1; idx_3 <= str3->len; ++idx_3)
            {
                for (register int idx_4 = 1; idx_4 <= str4->len; ++idx_4)
                {
                    for (register int idx_5 = 1; idx_5 <= str5->len; ++idx_5)
                    {
                        if (str1->data[idx_1 - 1] == str2->data[idx_2 - 1] && str1->data[idx_1 - 1] == str3->data[idx_3 - 1] && str1->data[idx_1 - 1] == str4->data[idx_4 - 1] && str1->data[idx_1 - 1] == str5->data[idx_5 - 1])
                        {
                            dp[idx_1][idx_2][idx_3][idx_4][idx_5] = dp[idx_1 - 1][idx_2 - 1][idx_3 - 1][idx_4 - 1][idx_5 - 1] + 1;
                        }
                        else
                        {
                            dp[idx_1][idx_2][idx_3][idx_4][idx_5] = max(dp[idx_1 - 1][idx_2][idx_3][idx_4][idx_5], max(dp[idx_1][idx_2 - 1][idx_3][idx_4][idx_5], max(dp[idx_1][idx_2][idx_3 - 1][idx_4][idx_5], max(dp[idx_1][idx_2][idx_3][idx_4 - 1][idx_5], dp[idx_1][idx_2][idx_3][idx_4][idx_5 - 1]))));
                        }
                    }
                }
            }
        }
    }

    // backtracking LCS
    int ans_idx = dp[str1->len][str2->len][str3->len][str4->len][str5->len];
    ans->data[ans_idx] = '\0';
    ans->len=ans_idx;
    register int idx_1 = str1->len;
    register int idx_2 = str2->len;
    register int idx_3 = str3->len;
    register int idx_4 = str4->len;
    register int idx_5 = str5->len;

    while (dp[idx_1][idx_2][idx_3][idx_4][idx_5] != 0)
    {

        if (dp[idx_1 - 1][idx_2][idx_3][idx_4][idx_5] == dp[idx_1][idx_2][idx_3][idx_4][idx_5])
        {
            --idx_1;
        }
        else if (dp[idx_1][idx_2 - 1][idx_3][idx_4][idx_5] == dp[idx_1][idx_2][idx_3][idx_4][idx_5])
        {
            --idx_2;
        }
        else if (dp[idx_1][idx_2][idx_3 - 1][idx_4][idx_5] == dp[idx_1][idx_2][idx_3][idx_4][idx_5])
        {
            --idx_3;
        }
        else if (dp[idx_1][idx_2][idx_3][idx_4 - 1][idx_5] == dp[idx_1][idx_2][idx_3][idx_4][idx_5])
        {
            --idx_4;
        }
        else if (dp[idx_1][idx_2][idx_3][idx_4][idx_5 - 1] == dp[idx_1][idx_2][idx_3][idx_4][idx_5])
        {
            --idx_5;
        }
        else
        {
            ans->data[--ans_idx] = str1->data[idx_1 - 1];
            --idx_1;
            --idx_2;
            --idx_3;
            --idx_4;
            --idx_5;
        }
    }

    // dealloc dp
    for (int i = 0; i <= str1->len; ++i)
    {
        for (int j = 0; j <= str2->len; ++j)
        {
            for (int k = 0; k <= str3->len; ++k)
            {
                for (int l = 0; l <= str4->len; ++l)
                {
                    free(dp[i][j][k][l]);
                }
                free(dp[i][j][k]);
            }
            free(dp[i][j]);
        }
        free(dp[i]);
    }
    free(dp);

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

    string user_input[MAX_STR];
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
        fgets(user_input[i].data, MAX_STR_LEN, input_file);
        user_input[i].len = strlen(user_input[i].data);
        if (user_input[i].data[user_input[i].len - 1] == '\n')
        {
            user_input[i].data[user_input[i].len - 1] = '\0';
            --user_input[i].len;
        }
    }
    fclose(input_file);

    string ans;
    if (number_of_strings == 2)
    {
        find_LCS2(&user_input[0], &user_input[1], &ans);
    }
    else if (number_of_strings == 3)
    {
        find_LCS3(&user_input[0], &user_input[1], &user_input[2], &ans);
    }
    else if (number_of_strings == 4)
    {
        find_LCS4(&user_input[0], &user_input[1], &user_input[2], &user_input[3],&ans);
    }
    else
    {
        find_LCS5(&user_input[0], &user_input[1], &user_input[2], &user_input[3], &user_input[4],&ans);
    }
    // find_LCS2(&user_input[0], &user_input[1], ans);
    //find_LCS3(&user_input[0], &user_input[1], &user_input[2], ans);

    printf("%s", ans);

    return 0;
}