//tarun
//230970005
//01-08-24
//Write a program using pipe to accept integer at parent and pass it to child. Child should check that number is Armstrong number
// or not and accordingly send a message - YES or NO to parent.
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
int main()
{
	int p1[2],p2[2],pid;
	pipe(p1);
	pipe(p2);
	
	pid=fork();
	if(pid<0)
	{
		perror("Error in creating fork");
		return 1;
	}
	else if(pid > 0)
	{
		int no;
		printf("Enter a number from the user:");
		scanf("%d",&no);
		printf("Done");
		close(p1[0]);
		close(p2[1]);
		
		write(p1[1],no,sizeof(no));
	printf("Write compelete in parent");
		wait(NULL);
		char str[5];
		read(p2[0],str,sizeof(str));
		printf("In parent str: %s",str);
	}
	if(pid==0)
	{
		printf("In child");
		close(p1[1]);
		close(p2[0]);
		int num;
		read(p1[0],num,sizeof(num));
		int temp=num,rem,sum=0;
		while(num!=0)
		{
			rem=num%10;
			sum=sum+rem*rem*rem;
			num=num/10;
		}
		if(sum==temp)
			write(p2[1],"Yes",sizeof("Yes"));
		else
			write(p2[1],"No",sizeof("No"));
	}

	return 0;
}
