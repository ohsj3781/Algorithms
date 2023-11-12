#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR 5
#define MAX_STR_LEN 121
#define MAX_ALLIGNED_STR_LEN 1024
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
    ans->len = ans_idx;
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
    ans->len = ans_idx;
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
    ans->len = ans_idx;
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
    ans->len = ans_idx;
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

void make_alligned_sequence(string *user_input, const int user_input_size, string *ans)
{
    char **aligned_str = (char **)calloc(user_input_size, sizeof(char *));
    for (int i = 0; i < user_input_size; ++i)
    {
        aligned_str[i] = (char *)calloc(MAX_ALLIGNED_STR_LEN, sizeof(char));
    }
    int *aligned_str_idx = (int *)calloc(user_input_size, sizeof(int));

    char aligned_ans[MAX_ALLIGNED_STR_LEN];
    int aligned_ans_idx = 0;

    char **last_str_ptr = (char **)calloc(user_input_size, sizeof(char *));
    char **str_ptr = (char **)calloc(user_input_size, sizeof(char *));
    for (int i = 0; i < user_input_size; ++i)
    {
        last_str_ptr[i] = user_input[i].data;
        str_ptr[i] = last_str_ptr[i];
    }
    // set aligned strings
    for (int i = 0; i < ans->len; ++i)
    {

        // find interval between alligned str element
        int aligned_interval = -1;
        for (int j = 0; j < user_input_size; ++j)
        {
            str_ptr[j] = strchr(last_str_ptr[j], ans->data[i]);
            aligned_interval = max(aligned_interval, str_ptr[j] - last_str_ptr[j]);
        }

        for (int str_idx = 0; str_idx < user_input_size; ++str_idx)
        {
            char *temp_str_ptr = last_str_ptr[str_idx];
            for (int j = 0; j < aligned_interval; ++j)
            {
                if (temp_str_ptr != str_ptr[str_idx])
                {
                    aligned_str[str_idx][aligned_str_idx[str_idx]] = *temp_str_ptr;
                    ++temp_str_ptr;
                }
                else
                {
                    aligned_str[str_idx][aligned_str_idx[str_idx]] = '-';
                }
                aligned_str_idx[str_idx]++;
            }
            aligned_str[str_idx][aligned_str_idx[str_idx]++] = *temp_str_ptr;
        }

        for (int j = 0; j < aligned_interval; ++j)
        {
            aligned_ans[aligned_ans_idx++] = ' ';
        }
        aligned_ans[aligned_ans_idx++] = '*';

        for (int j = 0; j < user_input_size; ++j)
        {
            last_str_ptr[j] = str_ptr[j] + 1;
        }
    }

    for (int i = 0; i < user_input_size; ++i)
    {
        str_ptr[i] = last_str_ptr[i];
    }

    int remain_str_max_len = -1;
    for (int str_idx = 0; str_idx < user_input_size; ++str_idx)
    {
        remain_str_max_len = max(remain_str_max_len, user_input[str_idx].len - (str_ptr[str_idx] - user_input[str_idx].data));
    }

    for (int str_idx = 0; str_idx < user_input_size; ++str_idx)
    {
        for (int remain_idx = 0; remain_idx < remain_str_max_len; ++remain_idx)
        {
            if (*str_ptr[str_idx] != '\0')
            {
                aligned_str[str_idx][aligned_str_idx[str_idx]] = *str_ptr[str_idx];
                ++str_ptr[str_idx];
            }
            else
            {
                aligned_str[str_idx][aligned_str_idx[str_idx]] = '-';
            }
            aligned_str_idx[str_idx]++;
        }
    }

    FILE* fp=fopen("hw2_output.txt","w");

    // out to hw2.out
    for (int i = 0; i < user_input_size; ++i)
    {
        aligned_str[i][aligned_str_idx[i]] = '\0';
        //printf("%s\n", aligned_str[i]);
        fprintf(fp,"%s\n",aligned_str[i]);
    }

    aligned_ans[aligned_ans_idx] = '\0';
    //printf("%s", aligned_ans);
    fprintf(fp,"%s",aligned_ans);

    fclose(fp);

    for (int i = 0; i < user_input_size; ++i)
    {
        free(aligned_str[i]);
    }
    free(aligned_str);

    free(aligned_str_idx);
    free(last_str_ptr);
    free(str_ptr);
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
    unsigned long long mem_size = 1;
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
        mem_size *= user_input[i].len;
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
        find_LCS4(&user_input[0], &user_input[1], &user_input[2], &user_input[3], &ans);
    }
    else
    {
        if (mem_size < (1 << 28))
        {
            find_LCS5(&user_input[0], &user_input[1], &user_input[2], &user_input[3], &user_input[4], &ans);
        }
        else
        {
            // find_LCS5_hisberg
        }
    }
    make_alligned_sequence(user_input, number_of_strings, &ans);
    // printf("%s", ans);

    return 0;
}