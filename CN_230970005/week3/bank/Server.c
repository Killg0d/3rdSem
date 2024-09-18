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
	
	int deposits,year,si,maturity;
	
	nread=read(fdc,&deposits,sizeof(deposits));
	if(nread)
	{
		read(fdc,&year,sizeof(year));
		if(year<=1)
		{
			si=(deposits*year*0.05)/100;
		}
		else if(year<=2)
		{	si=(deposits*year*0.06)/100;
		}
		else if(year<=3)
		{
			write(fdc,&(maturity),sizeof(maturity));
		}
		else
		{
			si=(deposits*year*0.08)/100;
		}
		maturity=deposits+si;
		printf("Year = %d Deposit = %d Si=%d",deposits,year,si);
		write(fdc,&(maturity),sizeof(maturity));
		write(fdc,&si,sizeof(si));
		
		 	
	}
	unlink("ClientFifo");
	//unlink("ServerFifo");	
	
	return 0;
}
