//tarun
//8-8-24
//230970005
//Write client-server program using named pipes. Client accepts Deposit amount and tenure (in years) and passes to server. Server has pre-stored information about different interest rates for different tenures. Accordingly, server applies appropriate interest rate and returns maturity amount and interest earned back to client.
//0-12 months 5% 
//13-24 months 6%
//25-36 months 7%
//>36 months 8%

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
	int months,deposits;
	printf("Enter deposit amount");
	scanf("%d",&deposits);
	printf("Enter tenure months");
	scanf("%d",&months);
	write(fdc,&deposits,sizeof(deposits));
	write(fdc,&months,sizeof(months));
	sleep(1);
	
	int maturity,interest;
	read(fdc,&maturity,sizeof(maturity));
	read(fdc,&interest,sizeof(interest));	
	printf("Maturity:%d\nInterest:%d\n",maturity,interest);
	return 0;
}
