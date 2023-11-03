#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAX_STR 5
#define MAX_STR_LEN 120

#define max(a,b) ((a)>(b) ? (a) : (b)) 

void find_LCS(char str1[], char str2[])
{
    static int matrix[MAX_STR_LEN + 1][MAX_STR_LEN + 1];
    const int str1_len = strlen(str1);
    const int str2_len = strlen(str2);

    for (int i = 0; i < MAX_STR_LEN + 1; ++i)
    {
        memset(matrix, 0, (MAX_STR_LEN + 1) * sizeof(int));
    }

    for(int i=1;i<=str1_len;++i){
        for(int j=1;j<=str2_len;++j){
            if(str1[i]==str2[j]){
                matrix[i][j]=matrix[i-1][j-1]+1;
            }
            else{
                matrix[i][j]=max(matrix[i-1][j],matrix[i][j-1]);
            }
            printf("%3d ",matrix[i][j]);
        }
        printf("\n");
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

    char strings[MAX_STR][MAX_STR_LEN + 1];
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
        fgets(strings[i], MAX_STR_LEN, input_file);
        strings[i][strlen(strings[i]) - 1] = '\0';
    }
    fclose(input_file);

    find_LCS(strings[0],strings[1]);
    return 0;
}