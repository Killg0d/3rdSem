// tarun shetty
// 230970005
// 31-07-2024
// Write a program to accept an array before forking and search the array in child for an element accepted and display the result.

#include "autoinclude.h"
#include<sys/wait.h>
int main()
{
    printf("Enter the size of array: ");
    int size;
    scanf("%d", &size);

    int narr[100]; // Increase array size to handle larger input
    printf("Enter the elements of array: ");
    for (int i = 0; i < size; i++)
    {
        scanf("%d", &narr[i]);
    }

    pid_t id = fork();
    if (id < 0)
    {
        perror("Error in creating fork");
        exit(1);
    }
    else if (id == 0)
    {
        /* child block where we will search */
        printf("Enter the element to search for: ");
        int searchElement;
        scanf("%d", &searchElement);
        int found = 0;
        for (int i = 0; i < size; i++)
        {
            if (narr[i] == searchElement)
            {
                found = 1;
                printf("Element %d found at index %d\n", searchElement, i);
                break;
            }
        }
        if (!found)
        {
            printf("Element %d not found in the array\n", searchElement);
        }
        exit(0); // Ensure child process exits after search
    }
    else
    {
        /* parent block */
        wait(NULL); // Wait for the child process to finish
    }

    return 0;
}
