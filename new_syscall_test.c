#include <linux/unistd.h>
#include <stdio.h>
#include <asm/unistd.h>

int main(int argc, char **argv)
{
	int i = syscall(337, argv[1], argv[2]);
	printf("successfully");
	printf("%d", i);
	return 1;
}