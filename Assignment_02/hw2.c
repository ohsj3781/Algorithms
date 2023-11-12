#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR 5
#define MAX_STR_LEN 122
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

void copy_str(char *dest, char *src, const int len)
{
    strncpy(dest, src, len);
    dest[len] = '\0';
}

void find_Hirschber_LCS(string *str1, string *str2, string *str3, string *str4, string *str5, string *ans)
{
    if (str1->len <= 0 || str2->len <= 0 || str3->len <= 0 || str4->len <= 0 || str5->len <= 0)
    {
        return;
    }
    else if (str1->len == 1)
    {
        for (register int idx_2 = 0; idx_2 < str2->len; ++idx_2)
        {
            for (register int idx_3 = 0; idx_3 < str3->len; ++idx_3)
            {
                for (register int idx_4 = 0; idx_4 < str4->len; ++idx_4)
                {
                    for (register int idx_5 = 0; idx_5 < str5->len; ++idx_5)
                    {
                        if (str1->data[0] == str2->data[idx_2] && str1->data[0] == str3->data[idx_3] && str1->data[0] == str4->data[idx_4] && str1->data[0] == str5->data[idx_5])
                        {
                            ans->data[0] = str1->data[0];
                            ans->len = 1;
                            ans->data[ans->len] = '\0';
                            return;
                        }
                    }
                }
            }
        }
        return;
    }

    // alloc mem
    char *****dp1 = (char *****)calloc(2, sizeof(char ****));

    for (int i = 0; i < 2; ++i)
    {
        dp1[i] = (char ****)calloc(str2->len + 2, sizeof(char ***));
        for (int j = 0; j < str2->len + 2; ++j)
        {
            dp1[i][j] = (char ***)calloc(str3->len + 2, sizeof(char **));
            for (int k = 0; k < str3->len + 2; ++k)
            {
                dp1[i][j][k] = (char **)calloc(str4->len + 2, sizeof(char *));
                for (int l = 0; l < str4->len + 2; ++l)
                {
                    dp1[i][j][k][l] = (char *)calloc(str5->len + 2, sizeof(char));
                }
            }
        }
    }

    const int mid = str1->len >> 1;
    for (register int idx_1 = 1; idx_1 <= mid; ++idx_1)
    {
        int now_idx = idx_1 % 2;
        int prev_idx = (now_idx + 1) % 2;
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
                            dp1[now_idx][idx_2][idx_3][idx_4][idx_5] = dp1[prev_idx][idx_2 - 1][idx_3 - 1][idx_4 - 1][idx_5 - 1] + 1;
                        }
                        else
                        {
                            dp1[now_idx][idx_2][idx_3][idx_4][idx_5] = max(dp1[prev_idx][idx_2][idx_3][idx_4][idx_5], max(dp1[now_idx][idx_2 - 1][idx_3][idx_4][idx_5], max(dp1[now_idx][idx_2][idx_3 - 1][idx_4][idx_5], max(dp1[now_idx][idx_2][idx_3][idx_4 - 1][idx_5], dp1[now_idx][idx_2][idx_3][idx_4][idx_5 - 1]))));
                        }
                    }
                }
            }
        }
    }

    char *****dp2 = (char *****)calloc(2, sizeof(char ****));

    for (int i = 0; i < 2; ++i)
    {
        dp2[i] = (char ****)calloc(str2->len + 2, sizeof(char ***));
        for (int j = 0; j < str2->len + 2; ++j)
        {
            dp2[i][j] = (char ***)calloc(str3->len + 2, sizeof(char **));
            for (int k = 0; k < str3->len + 2; ++k)
            {
                dp2[i][j][k] = (char **)calloc(str4->len + 2, sizeof(char *));
                for (int l = 0; l < str4->len + 2; ++l)
                {
                    dp2[i][j][k][l] = (char *)calloc(str5->len + 2, sizeof(char));
                }
            }
        }
    }

    // search_idx
    for (register int idx_1 = str1->len; idx_1 > mid; --idx_1)
    {
        int now_idx = idx_1 % 2;
        int prev_idx = (now_idx + 1) % 2;
        for (register int idx_2 = str2->len; idx_2 > 0; --idx_2)
        {
            for (register int idx_3 = str3->len; idx_3 > 0; --idx_3)
            {
                for (register int idx_4 = str4->len; idx_4 > 0; --idx_4)
                {
                    for (register int idx_5 = str5->len; idx_5 > 0; --idx_5)
                    {
                        if (str1->data[idx_1 - 1] == str2->data[idx_2 - 1] && str1->data[idx_1 - 1] == str3->data[idx_3 - 1] && str1->data[idx_1 - 1] == str4->data[idx_4 - 1] && str1->data[idx_1 - 1] == str5->data[idx_5 - 1])
                        {
                            dp2[now_idx][idx_2][idx_3][idx_4][idx_5] = dp2[prev_idx][idx_2 + 1][idx_3 + 1][idx_4 + 1][idx_5 + 1] + 1;
                        }
                        else
                        {
                            dp2[now_idx][idx_2][idx_3][idx_4][idx_5] = max(dp2[prev_idx][idx_2][idx_3][idx_4][idx_5], max(dp2[now_idx][idx_2 + 1][idx_3][idx_4][idx_5], max(dp2[now_idx][idx_2][idx_3 + 1][idx_4][idx_5], max(dp2[now_idx][idx_2][idx_3][idx_4 + 1][idx_5], dp2[now_idx][idx_2][idx_3][idx_4][idx_5 + 1]))));
                        }
                    }
                }
            }
        }
    }

    const int dp1_idx = mid % 2;
    const int dp2_idx = (dp1_idx + 1) % 2;

    int substr_idx2 = 0;
    int substr_idx3 = 0;
    int substr_idx4 = 0;
    int substr_idx5 = 0;
    int value = -1;
    int dp1_value = -1;
    int dp2_value = -1;
    for (register int idx_2 = 0; idx_2 <= str2->len; ++idx_2)
    {
        for (register int idx_3 = 0; idx_3 <= str3->len; ++idx_3)
        {
            for (register int idx_4 = 0; idx_4 <= str4->len; ++idx_4)
            {
                for (register int idx_5 = 0; idx_5 <= str5->len; ++idx_5)
                {
                    int temp_value = dp1[dp1_idx][idx_2][idx_3][idx_4][idx_5] + dp2[dp2_idx][idx_2 + 1][idx_3 + 1][idx_4 + 1][idx_5 + 1];
                    if (value < temp_value)
                    {
                        value = temp_value;
                        dp1_value = dp1[dp1_idx][idx_2][idx_3][idx_4][idx_5];
                        dp2_value = value - dp1_value;
                        substr_idx2 = idx_2;
                        substr_idx3 = idx_3;
                        substr_idx4 = idx_4;
                        substr_idx5 = idx_5;
                    }
                }
            }
        }
    }

    // dealloc mem
    for (int i = 0; i < 2; ++i)
    {
        for (int j = 0; j <= str2->len + 1; ++j)
        {
            for (int k = 0; k <= str3->len + 1; ++k)
            {
                for (int l = 0; l <= str4->len + 1; ++l)
                {
                    free(dp1[i][j][k][l]);
                }
                free(dp1[i][j][k]);
            }
            free(dp1[i][j]);
        }
        free(dp1[i]);
    }
    free(dp1);

    for (int i = 0; i < 2; ++i)
    {
        for (int j = 0; j <= str2->len + 1; ++j)
        {
            for (int k = 0; k <= str3->len + 1; ++k)
            {
                for (int l = 0; l <= str4->len + 1; ++l)
                {
                    free(dp2[i][j][k][l]);
                }
                free(dp2[i][j][k]);
            }
            free(dp2[i][j]);
        }
        free(dp2[i]);
    }
    free(dp2);

    // make sub_str
    string dp1_substr1, dp1_substr2, dp1_substr3, dp1_substr4, dp1_substr5;

    dp1_substr1.len = mid;
    copy_str(dp1_substr1.data, str1->data, dp1_substr1.len);

    dp1_substr2.len = substr_idx2;
    copy_str(dp1_substr2.data, str2->data, dp1_substr2.len);

    dp1_substr3.len = substr_idx3;
    copy_str(dp1_substr3.data, str3->data, dp1_substr3.len);

    dp1_substr4.len = substr_idx4;
    copy_str(dp1_substr4.data, str4->data, dp1_substr4.len);

    dp1_substr5.len = substr_idx5;
    copy_str(dp1_substr5.data, str5->data, dp1_substr5.len);

    string dp2_substr1, dp2_substr2, dp2_substr3, dp2_substr4, dp2_substr5;

    dp2_substr1.len = str1->len - dp1_substr1.len;
    copy_str(dp2_substr1.data, str1->data + mid, dp2_substr1.len);

    dp2_substr2.len = str2->len - dp1_substr2.len;
    copy_str(dp2_substr2.data, str2->data + substr_idx2, dp2_substr2.len);

    dp2_substr3.len = str3->len - dp1_substr3.len;
    copy_str(dp2_substr3.data, str3->data + substr_idx3, dp2_substr3.len);

    dp2_substr4.len = str4->len - dp1_substr4.len;
    copy_str(dp2_substr4.data, str4->data + substr_idx4, dp2_substr4.len);

    dp2_substr5.len = str5->len - dp1_substr5.len;
    copy_str(dp2_substr5.data, str5->data + substr_idx5, dp2_substr5.len);

    // add sub_ans_string
    string sub_ans1;
    memset(sub_ans1.data, 0, sizeof(char) * MAX_STR_LEN);
    sub_ans1.len = 0;
    string sub_ans2;
    memset(sub_ans2.data, 0, sizeof(char) * MAX_STR_LEN);
    sub_ans2.len = 0;

    find_Hirschber_LCS(&dp1_substr1, &dp1_substr2, &dp1_substr3, &dp1_substr4, &dp1_substr5, &sub_ans1);
    find_Hirschber_LCS(&dp2_substr1, &dp2_substr2, &dp2_substr3, &dp2_substr4, &dp2_substr5, &sub_ans2);

    strncpy(ans->data, sub_ans1.data, sub_ans1.len);

    strncat(ans->data, sub_ans2.data, sub_ans2.len);

    ans->len = sub_ans1.len + sub_ans2.len;

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

    FILE *fp = fopen("hw2_output.txt", "w");

    // out to hw2.out
    for (int i = 0; i < user_input_size; ++i)
    {
        aligned_str[i][aligned_str_idx[i]] = '\0';
        // printf("%s\n", aligned_str[i]);
        fprintf(fp, "%s\n", aligned_str[i]);
    }

    aligned_ans[aligned_ans_idx] = '\0';
    // printf("%s", aligned_ans);
    fprintf(fp, "%s", aligned_ans);

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
    memset(ans.data, 0, MAX_STR_LEN * sizeof(char));
    ans.len = 0;
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
            find_Hirschber_LCS(&user_input[0], &user_input[1], &user_input[2], &user_input[3], &user_input[4], &ans);
        }
    }
    make_alligned_sequence(user_input, number_of_strings, &ans);
    // printf("%s", ans);

    return 0;
}