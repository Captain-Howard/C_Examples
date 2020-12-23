/*
 ============================================================================
 Name        : howa621_reader.c
 Author      : Austin Howard
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>

#define MAX_BUF 1024

int main(void)
{
	int fd;
	char * myfifo = "/tmp/myfifo";
	char buf[MAX_BUF];

	/* open, read, and display the message from the FIFO */

	if ((fd = open(myfifo, O_RDONLY)) < 0)
	{
		perror("fifo creation failed");
		exit(EXIT_FAILURE);
	}
	if (read(fd, buf, MAX_BUF) < 0)
	{
		perror("fifo read failed");
		exit(EXIT_FAILURE);
	}
	printf("Received: %s\n", buf);
	if (close(fd) < 0)
	{
		perror("close descriptor failed");
		exit(EXIT_FAILURE);
	}

	return EXIT_SUCCESS;
}
