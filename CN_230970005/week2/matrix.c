// tarun
// 230970005
// 1/8/2024
// Write a program using pipe to accept a matrix on n X n and pass it to child. 
// Child will multiply each element of user’s choice to each element return new matrix back to parent.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>



int main()
{
    int p1[2], p2[2], pid;
    pipe(p1);
    pipe(p2);

    pid = fork();

    if (pid < 0)
    {
        perror("Error in creating fork");
        return 1;
    }
    else if (pid > 0) // Parent
    {
        int n, multiplier;
        printf("Enter the size of the matrix (n x n): ");
        scanf("%d", &n);
        fflush(stdin);
        int matrix[n][n];

        printf("Enter the elements of the matrix:\n");
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                scanf("%d", &matrix[i][j]);
            }
        }

        printf("Enter the multiplier: ");
        scanf("%d", &multiplier);
        // printf("Result:\n");
        // for (int i = 0; i < n; i++)
        // {
        //     for (int j = 0; j < n; j++)
        //     {
        //         printf("%d ", matrix[i][j]);
        //     }
        //     printf("\n");
        // }
        close(p1[0]); // Close read end of pipe1
        close(p2[1]); // Close write end of pipe2

        // Send matrix and multiplier to child
        write(p1[1], &n, sizeof(int));
        write(p1[1], &multiplier, sizeof(int));
        write(p1[1], matrix, sizeof(int) * n * n);

        fflush(stdout);
        wait(NULL); // Wait for child to complete

        int resultMatrix[n][n];
        read(p2[0], resultMatrix, sizeof(int) * n * n);

        printf("Resulting matrix after multiplication:\n");
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                printf("%d ", resultMatrix[i][j]);
            }
            printf("\n");
        }
    }

    if (pid == 0) // Child
    {
        close(p1[1]); // Close write end of pipe1
        close(p2[0]); // Close read end of pipe2

        int n, multiplier;
        
        
        // Read matrix and multiplier from parent
        read(p1[0], &n, sizeof(int));
        int matrix[n][n];
        read(p1[0], &multiplier, sizeof(int));
        for(int i=0;i<n;i++)
            read(p1[0], matrix[i], sizeof(int) * n);
        

        // printf("Resulting matrix:\n");
        // for (int i = 0; i < n; i++)
        // {
        //     for (int j = 0; j < n; j++)
        //     {
        //         printf("%d ", matrix[i][j]);
        //     }
        //     printf("\n");
        // }

        // Multiply each element of the matrix by the multiplier
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                matrix[i][j] *= multiplier;
            }
        }

        // Send the resulting matrix back to parent
        write(p2[1], matrix, sizeof(int) * n * n);

        printf("Child completed matrix multiplication.\n");
        fflush(stdout);
    }

    return 0;
}
