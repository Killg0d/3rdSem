// tarun shetty
// 230970005
// 31-07-2024
// Write a program to write some characters to a file and close it in the parent. Child should open the same file in child and display.
#include "autoinclude.h"

int main()
{
    char content[100];
    printf("Enter a filename:");
    char filename[100];
    scanf("%s", filename);
    // Clear input buffer before using fgets
    getchar();
    printf("Enter the content to write to the file: ");
    fgets(content, sizeof(content), stdin);

    int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (fd == -1)
    {
        perror("Error opening file in parent process");
        return 1;
    }

    if (write(fd, content, sizeof(content)) == -1)
    {
        perror("Error writing to file in parent process");
        close(fd);
        return 1;
    }

    close(fd);

    pid_t id = fork();
    if (id < 0)
    {
        perror("Error in creating fork");
        exit(1);
    }
    else if (id == 0)
    {
        /*child block where we will read*/

        int flags = O_RDONLY;
        int fd = open(filename, flags);
        if (fd == -1)
        {
            perror("Error in opening file:");
            exit(1);
        }

        char buffer[100];
        ssize_t bytesRead;

        bytesRead = read(fd, buffer, sizeof(buffer) - 1);
        if (bytesRead == -1)
        {
            perror("Error reading from stdin");
            return 1;
        }

        buffer[bytesRead] = '\0';
        printf("Read from stdin: %s\n", buffer);

        close(fd);
    }
    else
    {
        /*parent close*/
    }
}
