//tarun
//230970005
//22-8-24
//2.Write a client server program using message queue to simulate calculator operations (+, -, *, / between two numbers). Client accepts two numbers and operation to be performed from the user and writes to message queue. Server reads from message queue and performs the required operation to produce result. The server returns the result to client using message queue in order to display result.
#include "../autoinclude.h"

 struct msgbuf
{
	long mtype;
	int num1;
	int num2;
	char op;
};
struct msgbuf2
{
	long mtype;
	int result;
};
int main()
{
	int msqid;
	key_t key;
	struct msgbuf rcvbuf;
	struct msgbuf2 sndbuf;
	key = 12345;
	if ((msqid = msgget(key, 0666)) < 0)
		die("msgget()");
	//Receive an answer of message type 1.
	/* Syntax : ssize_t msgrcv(int msqid, void *msgp, size_t msgsz, long msgtyp, int
	msgflg); */
	size_t buflen=sizeof(rcvbuf)-sizeof(long);
	if (msgrcv(msqid, &rcvbuf, buflen, 1, 0) < 0)
		die("msgrcv");
	int result;
	int num1=rcvbuf.num1,num2=rcvbuf.num2;
	printf("%c",rcvbuf.op);
	switch (rcvbuf.op)
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
        sndbuf.result=result;
        printf("\n%d",sndbuf.result);
        sndbuf.mtype=2;
        if (msgsnd(msqid, &sndbuf, sizeof(int), IPC_NOWAIT) < 0)
	{
		//printf ("%d, %ld, %d, %d\n", msqid, sndbuf.mtype, sndbuf.result, buflen);
		die("msgsnd");
	}
	else
		printf("Message Sent");
	
	exit(0);
}
