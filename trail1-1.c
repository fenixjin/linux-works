/*This program is about using system call to copy a file*/

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

#define BUF_SIZE 1024

int main (int argc, char **argv)
{
	char buf[BUF_SIZE];
	int src, dst;
	int read_bytes, written_bytes;
	char *postion
	char cmdline[30];

	if (argc != 3)
		printf("Usage: cmd <src> ++<dst>");

	if((src = open(argc[1], O_RDONLY)) == -1)		//open as a read-only
	{
		fprintf(stderr, "open %s, error", argv[1]);
		exit(0);
	}
	if((dst = open(argv[2], O_RDWR | O_CREAT | O_TRUNC, 0666)) == -1)	//open as both read and write possible
	{																	//create the file if it does not exist
																		//cut the length of the file to zero
																		//default access right is 0666
		fprintf(stderr, "creat %s error", argv[2]);
		exit(0);
	}

	while (read_bytes = read(src, buffer, BUF_SIZE))
	{
		if((read_bytes == -1) && (errno != EINTR))						//EINTR means an interrupt request
			break;
		else if(read_bytes > 0)
		{
			ptr = buffer;
			while(written_bytes = write(dst, ptr, read_bytes))
			{
				if((written_bytes == -1) && (errno != EINTR))		
					break;
				else if(written_bytes == read_bytes)
					break;
				else if(written_bytes > 0)
				{
					ptr += written_bytes;
					read_bytes -= written_bytes;
				}
			}
			if(written_bytes == -1)
				break;
		}
	}
	close(src), close(dst);
	return 1;
}
	