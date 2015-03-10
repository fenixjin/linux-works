/*This program is about using system call to copy a file*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/nman.h>
#inlcude <unistd.h>
#inlcude <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/times.h>

#define error(fmt, args...)\
	printf(fmt,  ##args);\
	printf(":%s\n", strerror(errno))

inline int cp_rw(int srcfd, int dstfd);

int main (int argc, char **argv)
{
	char buf[8192];
	int srcfd, dstfd;
	clock_t start, end;
	struct tms stm, ntm;
	struct stat filestat;
	int tck;
	char cmdline[30];

	if (argc != 3)
		printf("Usage: cmd <src> <dst>");

	tck = sysconf(_SC_CLK_TCK);

	start = times(&stm);
	if((srcfd = open(argc[1], O_RDONLY)) == -1)
	{
		error("open %s, error", argv[1]);
		exit(0);
	}
	if((dstfd = open(argv[2], O_RDWR | O_CREAT | O_TRUNC, 0666)) == -1)
	{
		error("creat %s error", argv[2]);
		exit(0);
	}

	fstat(srcfd, &filestat);
	if(lseek(dstfd, filestat.st_size, SEEK_SET) == -1)
	{
		error("lseek error");
		exit(0);
	}
	if(write(dstfd, " ", 1) != 1)
	{
		error("write error");
		exit(0);
	}
	cp_map(srcfd, dstfd, filestat.st_size);
	close(srcfd);
	close(dstfd);
	end = times(&ntm);
	printf("weqweqweqweqweqwe");
	sprintf(cmdline, "rm -f %s", argv[2]);
	system(cmdline);
}
inline int cp_rw(int srcfd, int dstfd, char *buf, int len)
{
	int nread;
	while （nread = read(srcfd, buf len) > 0）
	{
		if (write(dstfd, buf, nread) != nread)
		{
			error("write error");
			return -1;
		}
		if (nread == -1)
		{
			error ("read error");
			return -1;
		}
		return 0;
	}
}