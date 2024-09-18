/*. Write a client-server socket program using TCP. 
Assume that Server has pre-stored information about
five Account number, PIN and Balance in a 3-dimensional array. 
Client accepts account number, pin and
withdrawal amount and sends to Server, 
if account holder is valid then performs withdrawal operations,
provided that enough balance is available otherwise display invalid
 Accno/PIN or No enough Balance.
Assume that account has to maintain 1000 minimum balance. 
If transaction is successful then server
display- “Withdrawal is successful and new balance:<New Balance value>” and 
same is sent to Client to
display.
*/
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
#include<unistd.h>
struct acc
{
    int accno;
    int password;
    int balance;
    int response;
}c;

int main() 
{
    
    int bank[5][3] = {
        {100, 1234, 999},   // First account: aacno, pin, amt
        {101, 5678, 5000},    // Second account
        {102, 4321, 7500},    // Third account
        {103, 8765, 12000},   // Fourth account
        {104, 1111, 9500}     // Fifth account
    };

    int sfd, ak, len;
    char buf1[50], buf2[50];
    struct sockaddr_in server, client;
    
    // Socket creation
    sfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sfd == -1) {
        printf("Socket creation error\n");
        exit(0);
    }

    // Server address setup
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_port = htons(3003);

    // Bind socket
    if (bind(sfd, (struct sockaddr*)&server, sizeof(server)) == -1) {
        printf("Bind error\n");
        close(sfd);
        exit(0);
    }

    len = sizeof(client);

    // Listen for connections
    listen(sfd, 5);

    // Accept connection
    ak = accept(sfd, (struct sockaddr*)&client, &len);
    if (ak == -1) {
        printf("Error in accepting connection\n");
        close(sfd);
        exit(0);
    }

    // Receive data from client
    recv(ak, &c, sizeof(c), 0);
    printf("CLIENT : ACCNO:%d\t PIN:%d", c.accno,c.password);
    c.response=1;
    for(int i=0;i<5;i++)
        {
            if(
                bank[i][0]==c.accno &&
                bank[i][1]==c.password
                )
                {
                    if(bank[i][2]>1000)
                    {   
                        c.response=0;
                        bank[i][2]-=c.balance;
                        c.balance=bank[i][2];
                    }
                }
        }
    // Print the classification result
    printf("\n%d\n", c.balance);

    // Send response to client
    send(ak, &c, sizeof(c), 0);

    // Close the socket descriptors
    close(ak);
    close(sfd);
    return 0;
}
