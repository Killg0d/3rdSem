//tarun
//8-8-24
//230970005
// Write client-server program using named pipes. Client accepts a string and passes to Server through a named pipe and server checks the string for palindrome and returns a message - YES or NO to Client.

#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>


int main()
{
	int fds,fdc;
	
	fdc=open("ClientFifo",O_RDWR);
	//fds=open("ServerFifo",O_RDONLY);
	
	if(fdc<0)
	{
		perror("Pipe opening failed");
		
		exit(1);
	}
	char string[64],nread[15];
	printf("Enter text to check palindrome:");
	scanf("%s",string);
	write(fdc,string,sizeof(string));
	sleep(1);
	fflush(stdin);fflush(stdout);
	int n=read(fdc,nread,sizeof(nread));	
	printf("%s %d",nread,n);
	return 0;
}
