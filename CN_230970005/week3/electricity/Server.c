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
    int fdc, nread;
    mkfifo("ClientFifo", 0666);

    fdc = open("ClientFifo", O_RDWR);
    if (fdc < 0) {
        perror("Pipe opening failed");
        unlink("ClientFifo");
        exit(1);
    }

    int customerNumber, unitsConsumed;
    double billAmount = 0;

    nread = read(fdc, &customerNumber, sizeof(customerNumber));
    if (nread) {
        read(fdc, &unitsConsumed, sizeof(unitsConsumed));

        if (unitsConsumed <= 50) 
	{
            billAmount = unitsConsumed * 1.0;
        } 
	else if (unitsConsumed <= 100) 
	{
            billAmount = (50 * 1.0) + ((unitsConsumed - 50) * 1.5);
        }
	 else if (unitsConsumed <= 200) 
	{
            billAmount = (50 * 1.0) + (50 * 1.5) + ((unitsConsumed - 100) * 2.0);
        }
	 else 
	{
            billAmount = (50 * 1.0) + (50 * 1.5) + (100 * 2.0) + ((unitsConsumed - 200) * 3.0);
        }
	printf("Bill =%f",billAmount);
        write(fdc, &billAmount, sizeof(billAmount));
    }
    
    unlink("ClientFifo");
    return 0;
}

