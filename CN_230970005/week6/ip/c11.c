#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<string.h>
#include<unistd.h>
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
		memset(buf1, '\0',sizeof(buf1));
	
		printf("CLIENT :enter ip address-");
		fgets(buf1,sizeof(buf1),stdin);
		buf1[strcspn(buf1, "\n")] = '\0';
		send(sfd,buf1,20,0);
		if(strcmp(buf1,"quit")==0)
		{	send(sfd,buf1,20,0);
			close(sfd);
			exit(0);
		}
		
		recv(sfd,buf2,sizeof(buf2),0);
		printf("SERVER : %s\n",buf2);
	
	close(sfd);
	return 0;
}
