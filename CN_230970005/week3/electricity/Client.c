//tarun
//21-08-24
//230970005
/*Write client-server program using named pipes. Client accepts - electricity customer number and number of units consumed.
Server calculates the bill by applying different rate for different slabs of units consumed.
0- 50 units @ 1/- per unit.
51-100 units @1.5/- per unit.
101-200 units @ 2/- per unit.
>200 units @ 3/- per unit*/
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

int main() {
    int fdc;
    mkfifo("ClientFifo", 0666);

    fdc = open("ClientFifo", O_RDWR);
    if (fdc < 0) {
        perror("Pipe opening failed");
        unlink("ClientFifo");
        exit(1);
    }

    int customerNumber, unitsConsumed;
    double billAmount;

    printf("Enter customer number: ");
    scanf("%d", &customerNumber);
    printf("Enter units consumed: ");
    scanf("%d", &unitsConsumed);

    write(fdc, &customerNumber, sizeof(customerNumber));
    write(fdc, &unitsConsumed, sizeof(unitsConsumed));
    sleep(1);
    read(fdc, &billAmount, sizeof(billAmount));
    printf("Customer Number: %d\n", customerNumber);
    printf("Units Consumed: %d\n", unitsConsumed);
    printf("Bill Amount: %.2f\n", billAmount);

    unlink("ClientFifo");
    return 0;
}

