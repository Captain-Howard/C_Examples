/*
 ============================================================================
 Name        : howa721_server.c
 Author      : Austin Howard
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define SHMSZ     1024

int main()
{
    char c;
    int shmid, input;
    int value = 0;
    key_t key;
    char *shm, *s;

    /*
     * We'll name our shared memory segment
     * "5678".
     */
    key = 5678;

    /*
     * Create the segment.
     */
    if ((shmid = shmget(key, SHMSZ, IPC_CREAT | 0666)) < 0) {
        perror("shmget");
        exit(EXIT_FAILURE);
    }

    /*
     * Now we attach the segment to our data space.
     */
    if ((shm = shmat(shmid, NULL, 0)) == (char *) -1) {
        perror("shmat");
        exit(EXIT_FAILURE);
    }

    /*
     * Now put some things into the memory for the
     * other process to read.
     */

    printf("Please enter a positive integer <= 100");
    scanf("%d", input);
    while(input > 100 || input < 2){
        printf("Please enter a positive integer <= 100");
        scanf("%d", input);
    }

    s = shm;

    *s = input;

    while(input > 0){
    	input -= 2;
    	value++;
    }

    for (c = 'a'; c <= 'z'; c++)
        *s++ = c;
    *s = NULL;

    /*
     * Finally, we wait until the other process
     * changes the first character of our memory
     * to '*', indicating that it has read what
     * we put there.
     */
    printf("Waiting for client to finish\n");
    while (*shm != '*')
        sleep(1);

    for(s = shm; *s != NULL; s++){
    	putchar(*s);
    }
    putchar("\n");

	if (shmdt(shm) < 0) {
		perror("Server detach segment error");
		exit(EXIT_FAILURE);
	}

    if(shmctl(shmid, IPC_RMID, NULL)< 0)
    {
    	perror("Server error destroying segment");
    	exit(EXIT_FAILURE);
    }

    return(EXIT_SUCCESS);
}

