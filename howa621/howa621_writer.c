/*
 ============================================================================
 Name        : howa621_writer.c
 Author      : Austin Howard
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>

int main(void)
{

	int fd;
	char * myfifo = "/tmp/myfifo";
	char input[50];

	/* create the FIFO (named pipe) */
	if (mkfifo(myfifo, 0666))
	{
		perror("fifo creation failed");
		exit(EXIT_FAILURE);
	}
	printf("Input a string up to 50 characters long: ");
	fgets(input, 50, stdin);
	/* write "Hi" to the FIFO */
	if ((fd = open(myfifo, O_WRONLY)) < 0)
	{
		perror("fifo open failed");
		exit(EXIT_FAILURE);

	}
	if (write(fd, &input, sizeof(input)) < 0)
	{
		perror("fifo write failed");
		exit(EXIT_FAILURE);

	}
	if (close(fd) < 0)
	{
		perror("descriptor close failed");
		exit(EXIT_FAILURE);

	}

	/* remove the FIFO */
	if (unlink(myfifo) < 0)
	{
		perror("fifo unlink failed");
		exit(EXIT_FAILURE);

	}

	return EXIT_SUCCESS;
}
