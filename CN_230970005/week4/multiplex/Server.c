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
	int tickets[5] = {20, 20, 20, 20, 20};
	int msqid;
	key_t key;
	struct msgbuf rcvbuf;
	key = 1234;
	if ((msqid = msgget(key, 0666)) < 0)
		die("msgget()");
	//Receive an answer of message type 1.
	/* Syntax : ssize_t msgrcv(int msqid, void *msgp, size_t msgsz, long msgtyp, int
	msgflg); */
	size_t buflen=sizeof(rcvbuf)-sizeof(long);
	if (msgrcv(msqid, &rcvbuf, buflen, 1, 0) < 0)
		die("msgrcv");
	int num=rcvbuf.cat-1;
	if(rcvbuf.no_of_tickets<tickets[num])
	{
		tickets[num]-=rcvbuf.no_of_tickets;
		rcvbuf.response=0;
	}
        rcvbuf.mtype=2;
        if (msgsnd(msqid, &rcvbuf, buflen, IPC_NOWAIT) < 0)
	{
		die("msgsnd");
	}
	else
		printf("Message Sent");
	
	exit(0);
}
