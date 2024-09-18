#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
#include<unistd.h>

int main() 
{
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
    recv(ak, buf1, 20, 0);
    printf("CLIENT : %s\n", buf1);
    
    // If client sends 'quit', close connection and exit
    if (strcmp(buf1, "quit") == 0) {
        close(sfd);
        close(ak);
        exit(0);
    }

    // Parse the received IP address and classify
    int ip[4], l = 0;
    char *token = strtok(buf1, ".");
    while (token != NULL && l < 4) {
        ip[l++] = atoi(token);  // Convert string to integer and store in ip array
        token = strtok(NULL, ".");
    }

    // Print the parsed IP address
    printf("\n%d.%d.%d.%d\n", ip[0], ip[1], ip[2], ip[3]);

    // Prepare response string
    char str[256];
    if (ip[0] > 0 && ip[0] < 128) {
        snprintf(str, sizeof(str), 
            "Class: A\nDefault Mask: 255.0.0.0\nNetwork Address: %d.0.0.0\nBroadcast Address: %d.255.255.255", 
            ip[0], ip[0]);
    } else if (ip[0] > 127 && ip[0] < 192) {
        snprintf(str, sizeof(str), 
            "Class: B\nDefault Mask: 255.255.0.0\nNetwork Address: %d.%d.0.0\nBroadcast Address: %d.%d.255.255", 
            ip[0], ip[1], ip[0], ip[1]);
    } else if (ip[0] > 191 && ip[0] < 224) {
        snprintf(str, sizeof(str), 
            "Class: C\nDefault Mask: 255.255.255.0\nNetwork Address: %d.%d.%d.0\nBroadcast Address: %d.%d.%d.255", 
            ip[0], ip[1], ip[2], ip[0], ip[1], ip[2]);
    } else if (ip[0] > 223 && ip[0] < 240) {
        snprintf(str, sizeof(str), 
            "Class: D (Multicast)\nDefault Mask: N/A\nNetwork Address: N/A\nBroadcast Address: N/A");
    } else if (ip[0] > 239 && ip[0] < 256) {
        snprintf(str, sizeof(str), 
            "Class: E (Reserved)\nDefault Mask: N/A\nNetwork Address: N/A\nBroadcast Address: N/A");
    }

    // Print the classification result
    printf("\n%s\n", str);

    // Send response to client
    send(ak, str, sizeof(str), 0);

    // Close the socket descriptors
    close(ak);
    close(sfd);
    return 0;
}
