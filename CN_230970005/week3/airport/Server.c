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

#define MAX_TRIPS 3

typedef struct {
    char source[20];
    char destination[20];
    int ticket_rate;
    int seats_available;
} Trip;

Trip trips[MAX_TRIPS] = {
    {"Mumbai", "Delhi", 100, 50},
    {"Mumbai", "Bangalore", 150, 30},
    {"Delhi", "Bangalore", 200, 20}
};

int main() {
    int fdc, nread;
    mkfifo("ClientFifo", 0666);

    fdc = open("ClientFifo", O_RDWR);
    if (fdc < 0) {
        perror("Pipe opening failed");
        unlink("ClientFifo");
        exit(1);
    }

    char passenger_name[50], source[20], destination[20];
    int seats_requested, found = 0, bill_amount = 0;

    nread = read(fdc, &passenger_name, sizeof(passenger_name));
    if (nread) {
        read(fdc, &source, sizeof(source));
        read(fdc, &destination, sizeof(destination));
        read(fdc, &seats_requested, sizeof(seats_requested));

        for (int i = 0; i < MAX_TRIPS; i++) {
            if (strcmp(source, trips[i].source) == 0 && strcmp(destination, trips[i].destination) == 0) {
                found = 1;
                if (trips[i].seats_available >= seats_requested) {
                    trips[i].seats_available -= seats_requested;
                    bill_amount = seats_requested * trips[i].ticket_rate;
                    write(fdc, &bill_amount, sizeof(bill_amount));
                } else {
                    bill_amount = -1;  // Indicate seats not available
                    write(fdc, &bill_amount, sizeof(bill_amount));
                }
                break;
            }
        }

        if (!found) {
            bill_amount = -1;  // Indicate route not found
            write(fdc, &bill_amount, sizeof(bill_amount));
        }
    }

    close(fdc);
    unlink("ClientFifo");
    return 0;
}

