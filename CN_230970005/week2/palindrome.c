//tarun
//230970005
//1-8-24
// Write a program using pipe to accept a string and pass it to child.
// Child will check the string whether it is palindrome or not. 
// If palindrome then return message PALLINDROME otherwise NOT PALLINDROME to Parent.

#include "autoinclude.h";

int main()
{
    int pd,p1[2],p2[2];
    pipe(p1);
    pipe(p2);
    pd=fork();
    if(pd<0)
    {
        perror("\nError in fork");
        return -1;
    }
    if(pd>0)
    {
        char str[20];
        printf("\nEnter a string:");
        scanf("%s",str);
        
        close(p1[0]);
        close(p2[1]);

        write(p1[1],str,sizeof(str));
        wait(NULL);
        char strng[20];
        read(p2[0],strng,sizeof(strng));
        printf("%s",strng);

    }
    if(pd==0)
    {
        close(p1[1]);
        close(p2[0]);
        char string[20];

        read(p1[0],string,sizeof(string));
        
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

        if(temp)
            write(p2[1],"Not Palindrome",sizeof("Not Palindrome"));
        else
            write(p2[1],"Palindrome",sizeof("Palindrome"));

            
    }
    
}