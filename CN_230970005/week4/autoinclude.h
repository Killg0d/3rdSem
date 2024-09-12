#ifndef AUTOINCLUDE_H
#define AUTOINCLUDE_H
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
void die(char *s)
{
	perror(s);
	exit(0);
}
#endif
