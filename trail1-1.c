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

inline int cp_rw(int srcfd, int dstfd)