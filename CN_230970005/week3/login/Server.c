//tarun
//8-8-24
//230970005
// Write client-server program using named pipes. Client accepts Username, password from user and passes them to server for authentication. Server has pre-stored username and passwords and it compares username and passwords and returns message -Welcome <username> or Login Access denied.
#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<stdlib.h>


int main()
{
	int fds,fdc,fc,fs,nread;
	fc=mkfifo("ClientFifo",0666);
	//fs=mkfifo("ServerFifo",0666);
	if(fc<0)
	{	
		perror("Pipe creation failed");
		unlink("ClientFifo");
		exit(1);
	}
	fdc=open("ClientFifo",O_RDWR);
	//fds=open("ServerFifo",O_WRONLY);
	
	if(fdc<0)
	{
		perror("Pipe opening failed");
		unlink("ClientFifo");
		exit(1);
	}
	char cuser[20],cpass[20];
	nread=read(fdc,cuser,sizeof(cuser));
	read(fdc,cpass,sizeof(cpass));
	if(nread)
	{
		if(strcmp(cuser,"Hello123")==0 && strcmp(cpass,"World123")==0)
		{
			char welcome[30]="Welcome ";
			strcat(welcome,cuser);
			write(fdc,welcome,sizeof(welcome));
		}
		else
			write(fdc,"Login denied",sizeof("Login denied"));
	}
	unlink("ClientFifo");
	//unlink("ServerFifo");	
	
	return 0;
}
