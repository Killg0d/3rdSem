// tarun shetty
// 230970005
// 31-07-2024
// Write a program to accept an array before forking and sort the array in child and display.


#include "autoinclude.h"

int main()
{
    printf("Enter the size of array");
    int size;
    scanf("%d",&size);
    int narr[10];
    printf("Enter the elements of array");
    for(int i=0;i<size;i++)
        scanf("%d",&narr[i]);
    pid_t id = fork();
    if (id < 0)
    {
        perror("Error in creating fork");
        exit(1);
    }
    else if (id == 0)
    {
        /*child block where we will read*/
        for(int i=0;i<size;i++)
        {
            for(int j=size-1;j>i;j--)
            {
                if(narr[i]>narr[j])
                {
                    int temp=narr[i];
                    narr[i]=narr[j];
                    narr[j]=temp;
                }
            }
        }
        printf("Elements of arr are:");
        for(int i=0;i<size;i++)
        {
            printf("%d\t",narr[i]);
        }
    }
    else
    {
        /*parent close*/
    }
}
