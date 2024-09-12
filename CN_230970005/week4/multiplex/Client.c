//tarun
//230970005
//22-8-24
//4. Write a client server program using message queue to book multiplex tickets. Assume that there are 5 ticket categories and each category there are 20 tickets. Assume that this is pre-stored information and available at server. From client program, User inputs- Name, Phone no, Ticket category and Number of tickets and pass it to server for ticket reservation. Depending on users input, decrement the number of seats in corresponding category, send booking information to client for displaying on the screen.
#include "../autoinclude.h"
struct msgbuf
{
	long mtype;
	char name[20];
	int phone;
	int cat;
	int no_of_tickets;
	int response;
};
int main()
{
	int msqid;
	int msgflg = IPC_CREAT | 0666;
	key_t key;
	struct msgbuf rcvbuf,sbuf;
	size_t buflen;
	key=1234;
	if ((msqid = msgget(key, msgflg )) < 0) //Get the message queue ID for the given key
		die("msgget");
	sbuf.mtype = 1;
	
	printf("\nEnter name:");
	scanf("%s",sbuf.name);
	printf("\nEnter phone:");
	scanf("%d",&sbuf.phone);
	do
	{
		printf("\nEnter category(1-5):");
		scanf("%d",&sbuf.cat);
	}while(sbuf.cat<1||sbuf.cat>5);
	printf("\nEnter no_of_tickets:");
	scanf("%d",&sbuf.no_of_tickets);

	buflen=sizeof(struct msgbuf)-sizeof(long);
	if (msgsnd(msqid, &sbuf, buflen, IPC_NOWAIT) < 0)
	{
		die("msgsnd");
	}
	else
		printf("Message Sent");
	if (msgrcv(msqid, &rcvbuf, buflen, 2, 0) < 0)
		die("msgrcv");
	if(rcvbuf.response==0)
	{
		printf("\nName:%s\nPhone:%d\nCategory:%d\nNo of tickets:%d\n",sbuf.name,sbuf.phone,sbuf.cat,sbuf.no_of_tickets);
	}
	else
	{
		printf("\nTicket not available");
	}
	printf("\n");
	return 0;
}
