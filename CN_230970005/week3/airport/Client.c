//tarun
//21-08-24
//230970005
/*Write client-server program using named pipes. Client accepts - passenger
 name, source, destination and number of seats and sends
to server. Assume that server has pre-stored information about
- Source, Destination, ticket_rate and number of seats available.
On receival of information from client, server checks for availability of 
seats. If available, accordingly decrement seats and sends 
bill amount to client, otherwise display message to client that
 -Seats not available*/
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int fdc;
    mkfifo("ClientFifo", 0666);

    fdc = open("ClientFifo", O_RDWR);
    if (fdc < 0) {
        perror("Pipe opening failed");
        unlink("ClientFifo");
        exit(1);
    }

    char passenger_name[50], source[20], destination[20];
    int seats_requested, bill_amount;

    printf("Enter passenger name: ");
    scanf("%s", passenger_name);
    printf("Enter source: ");
    scanf("%s", source);
    printf("Enter destination: ");
    scanf("%s", destination);
    printf("Enter number of seats: ");
    scanf("%d", &seats_requested);

    write(fdc, &passenger_name, sizeof(passenger_name));
    write(fdc, &source, sizeof(source));
    write(fdc, &destination, sizeof(destination));
    write(fdc, &seats_requested, sizeof(seats_requested));
    sleep(1);
    read(fdc, &bill_amount, sizeof(bill_amount));

    if (bill_amount == -1) {
        printf("Seats not available or route not found.\n");
    } else {
        printf("Booking successful! Bill Amount: %d\n", bill_amount);
    }

    close(fdc);
    unlink("ClientFifo");
    return 0;
}
