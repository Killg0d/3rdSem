#include <stdlib.h>
#include <stdio.h>
int main(void)
{
   int val;
   char *str; 
   str = "121.1.1.1";
   val = atoi(str); 
   
   printf("integral number = %d", val);
}
