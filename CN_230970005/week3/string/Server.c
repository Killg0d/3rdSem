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
	char string[64];
	nread=read(fdc,string,sizeof(string));
	if(nread)
	{
		//Palindrome
		int len=0;
		for(;string[len]!='\0';len++);
		
		int rev = len - 1;
		int temp = 0;
		for (int i = 0; i < len / 2; i++) {
		    if (string[i] != string[rev - i]) {
		        temp = 1;
		        break;
		    }
		}
		printf("%d Working",temp);
		if(temp)
		  write(fdc,"Not Palindrome",sizeof("Not Palindrome"));
		else
		 write(fdc,"Palindrome",sizeof("Palindrome"));
	}
	unlink("ClientFifo");
	//unlink("ServerFifo");	
	
	return 0;
}
