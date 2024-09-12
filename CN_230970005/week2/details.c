// tarun
// 230970005
// 1/8/2024
// Write a program using pipe to accept details
// of a student such as
// - RegNo, Mark1, Mark2, Mark3 and send it to child.
// Child will find average and accordingly assign
// Grades (A+, A, B, C, D, E, F- assume some criteria)
// and return grade to Parent.

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
        int rno, marks[3];
        printf("\nEnter Regno:");
        scanf("%d", &rno);

        printf("\nEnter the Marks:");
        for (int i = 1; i <= 3; i++)
        {
            scanf("%d", &marks[i - 1]);
        }

        close(p1[0]); // close read of parent in one pipe
        close(p2[1]); // close write of child in another

        write(p1[1], marks, sizeof(marks));
        fflush(stdout);
        printf("\nWrite compelete in parent");
        wait(NULL);
        fflush(stdout);
        char g;
        read(p2[0], &g, sizeof(char));
        printf("%d grade is %c", rno, g);
    }

    if (pid == 0)
    {
        printf("\nIn child");
        fflush(stdout);
        close(p1[1]); // close write of parent in pipe1
        close(p2[0]); // close read of child in pipe2
        int mrk[3];

        read(p1[0], mrk, sizeof(int) * 3);
        char grade;
        int total = mrk[0] + mrk[1] + mrk[2];
        int average = total / 3;

        if (mrk[0] < 35 || mrk[1] < 35 || mrk[2] < 35)
        {
            grade = 'F';
        }
        else
        {
            switch (average / 10)
            {
            case 10:
            case 9:
                grade = 'A';
                break;
            case 8:
                grade = 'B';
                break;
            case 7:
                grade = 'C';
                break;
            case 6:
                grade = 'D';
                break;
            default:
                grade = 'F';
                break;
            }
        }

        write(p2[1], &grade, sizeof(char));

        printf("\nChild completed");
        fflush(stdout);
    }

    return 0;
}
