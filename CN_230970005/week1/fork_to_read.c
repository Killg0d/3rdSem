// tarun shetty
// 230970005
// 31-07-2024
// Read name fork in child read 10 char

#include "autoinclude.h"

int main()
{
    printf("Enter a filename:");
    char *file;
    scanf("%s", file);

    int flags = O_RDONLY;
    int fd = open(file, flags);
    if (fd == -1)
    {
        perror("Error in opening file:");
        exit(1);
    }
    
    
    pid_t id = fork();
    
    if (id < 0)
    {
        perror("Error in creating fork");
        exit(1);
    }
    
    else if (id == 0)
    {
        /*child block where we will read*/
        
        char buffer[10];
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
