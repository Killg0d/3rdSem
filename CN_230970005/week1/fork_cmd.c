// tarun shetty
// 230970005
// 31-07-2024
// Accept two numbers and operator (+, -, *, /) as command line arguments. Perform numerical operation as per operator in the child and display the result.
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        fprintf(stderr, "Usage: %s <num1> <operator> <num2>\n", argv[0]);
        return 1;
    }

    double num1 = atof(argv[1]);
    double num2 = atof(argv[3]);
    char operator = argv[2][0];
    double result;

    pid_t id = fork();
    if (id < 0)
    {
        perror("Error in creating fork");
        exit(1);
    }
    else if (id == 0)
    {
        // Child process
        switch (operator)
        {
        case '+':
            result = num1 + num2;
            break;
        case '-':
            result = num1 - num2;
            break;
        case '*':
            result = num1 * num2;
            break;
        case '/':
            if (num2 == 0)
            {
                fprintf(stderr, "Error: Division by zero\n");
                exit(1);
            }
            result = num1 / num2;
            break;
        default:
            fprintf(stderr, "Invalid operator\n");
            exit(1);
        }
        printf("Result: %f\n", result);
        exit(0);
    }
    else
    {
        // Parent process
        wait(NULL);
    }
    return 0;
}
