//tarun
//8-8-24
//230970005
// Write client-server program using named pipes. Client accepts Username, password from user and passes them to server for authentication. Server has pre-stored username and passwords and it compares username and passwords and returns message -Welcome <username> or Login Access denied.
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
	char username[20],password[15],result[30];
	printf("Enter username:");
	scanf("%s",username);
	
	printf("Enter password:");
	scanf("%s",password);
	write(fdc,username,sizeof(username));
	write(fdc,password,sizeof(password));
	sleep(1);
	fflush(stdin);fflush(stdout);
	int n=read(fdc,result,sizeof(result));	
	printf("%s %d",result,n);
	return 0;
}
