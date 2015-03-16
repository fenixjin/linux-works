#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <linux/sem.h>

int semid, p1, p2;
char *finish;
int main(void)
{
	if((p1 = fork()) == 0)
	{
		execv("./S1", NULL);
	}
	else
	{
		if((p2 = fork()) == 0)
		{
			execv("./S2", NULL);
		}
		else
		{
			execv("./S3", NULL);
		}
	}
	return 0;
}