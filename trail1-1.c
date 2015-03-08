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