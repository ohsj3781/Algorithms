#include <stdio.h>
#include <stdlib.h>

void insert(int element)
{}

int delete_min() {}

int delete_max() {}

int delete_median() {}

int find_min() {}

int find_max() {}

int find_median() {}

int main()
{

    printf("Hello Ubuntu");

    int N;
    scanf("%d", &N);

    char option1,option2_c;
    int option2_i;

    while (N--)
    {
        scanf("%c", &option1);
        if(option1=='I'){
            scanf("%d",option2_i);
            insert(option2_i);
        }
        else{
            scanf("%c", &option2_c);
            if(option1=='D'){
                if(option2_c=='M'){

                }
                else if(option2_c=='X'){

                }
                else{

                }
            }
            //option1_c=='F' 
            else{
                if(option2_c=='M'){

                }
                else if(option2_c=='X'){

                }
                else{
                    
                }
            }

        }
    }

    return 0;
}