/*. Write a client-server socket program using TCP. 
Assume that Server has pre-stored information about
five Account number, PIN and Balance in a 3-dimensional array. 
Client accepts account number, pin and
withdrawal amount and sends to Server, 
if account holder is valid then performs withdrawal operations,
provided that enough balance is available otherwise display "invalid
 Accno/PIN or No enough Balance.
Assume that account has to maintain 1000 minimum balance. 
If transaction is successful then server
display- “Withdrawal is successful and new balance:<New Balance value>” and 
same is sent to Client to
display.
*/

#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<stdlib.h>
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
	int sfd,res;
	char buf1[50],buf2[256];
	struct sockaddr_in server;
	sfd=socket(AF_INET,SOCK_STREAM,0);
	if(sfd==-1)
	{	printf("socket creation error");
		exit(0);
	}
	server.sin_family=AF_INET;
	server.sin_addr.s_addr=inet_addr("127.0.0.1");
	server.sin_port=htons(3003);
	res=connect(sfd,(struct sockaddr*)&server,sizeof(server));
	if(res==-1)
	{	printf("connection error");
		exit(0);
	}
		printf("CLIENT -\nEnter accno:");
		scanf("%d",&c.accno);
		printf("\nEnter password:");
		scanf("%d",&c.password);
		printf("\nEnter balance:");
		scanf("%d",&c.balance);
        
        send(sfd,&c,sizeof(c),0);
		
		recv(sfd,&c,sizeof(c),0);
        if(c.response==1)
        {
            printf("\nInvalid  Accno/PIN or No enough Balance.");
        }
        else{
		    printf("SERVER : “Withdrawal is successful and new balance:%d\n",c.balance);
        }
	close(sfd);
	return 0;
}
