// tarun
// 230970005
// 1/8/2024
// Write a program using pipe to accept an array of integers
// at parent and pass it to child. Child will pick only even
// numbers and return array of even numbers to parent.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
int main()
{
    int p1[2], p2[2], pid;
    pipe(p1);
    pipe(p2);
    // two pipes for two uni-way communication
    // pipe1 will write from parent and read in child
    // pipe2 will write in child and read in parent
    pid = fork();

    if (pid < 0)
    {
        perror("Error in creating fork");
        return 1;
    }
    else if (pid > 0) // parent
    {
        int no;
        printf("\nEnter size:");
        scanf("%d", &no);
        int num[no];
        printf("\nEnter the elements:");
        for (int i = 0; i < no; i++)
        {
            scanf("%d", &num[i]);
        }

        close(p1[0]); // close read of parent in one pipe
        close(p2[1]); // close write of child in another

        write(p1[1], &no, sizeof(no));
        write(p1[1], num, sizeof(int) * no);
        printf("\nWrite compelete in parent");
        wait(NULL);
        int n;
        read(p2[0], &n, sizeof(n));
        int evenp[n];
        read(p2[0], evenp, sizeof(int) * n);
        printf("\nIn parent even array is:");
        for (int i = 0; i < n; i++)
        {
            printf("%d\t", evenp[i]);
        }
    }
    if (pid == 0)
    {
        printf("\nIn child");
        close(p1[1]); // close write of parent in pipe1
        close(p2[0]); // close read of child in pipe2
        int size;
        read(p1[0], &size, sizeof(size));
        int arr[size];
        read(p1[0], arr, sizeof(int) * size);

        int even_size = 0;
        int evenarr[size];
        for (int i = 0; i < size; i++)
        {
            if (arr[i] % 2 == 0)
            {
                evenarr[even_size++] = arr[i];
            }
        }
        fflush(stdin);
        write(p2[1], &even_size, sizeof(even_size));
        write(p2[1], evenarr, sizeof(int) * even_size);
        printf("\nChild completed");
    }

    return 0;
}
