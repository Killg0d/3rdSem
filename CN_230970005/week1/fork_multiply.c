// tarun shetty
// 230970005
// 31-07-2024
//Write a program to accept an integer before forking and child has to generate multiplication table corresponding to the integer.
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void generate_multiplication_table(int num) {
    printf("Multiplication Table for %d:\n", num);
    for (int i = 1; i <= 10; i++) {
        printf("%d x %d = %d\n", num, i, num * i);
    }
}

int main() {
    pid_t pid;
    int num;

    // Accept an integer from the user
    printf("Enter an integer: ");
    scanf("%d", &num);

    // Fork a new process
    pid = fork();

    if (pid < 0) {
        // Error occurred
        fprintf(stderr, "Fork Failed");
        return 1;
    } else if (pid == 0) {
        // Child process
        generate_multiplication_table(num);
        exit(0);
    } else {
        // Parent process
        // Wait for the child to complete
        wait(NULL);
        printf("Child process completed.\n");
    }

    return 0;
}
