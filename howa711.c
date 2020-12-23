/*
 ============================================================================
 Name        : howa711.c
 Author      : Austin Howard
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */


#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>


int main(void)
{

    int shmemid;
    int *shmbuf;
    pid_t pid;
    const int BUFFSIZE=2048; /* size of shared mem */
    int i;
    int capacity;

    //Getting input from user
    int input, inputitems;
    printf("Please enter in the amount of Fibonnacci numbers: ");
    inputitems = scanf("%d", &input);
    if(inputitems == EOF){
    	printf("EOF failure!");
    }
    else if(inputitems == 0){
    	printf("No match!");
    }
    else{
    	printf("You entered %d\n", input);
    }

    while(input < 0 || input > 50){
    	printf("Please enter a number between 0-50\n ");
        printf("Please enter in the amount of Fibonnacci numbers: ");
        inputitems = scanf("%d", &input);
        if(inputitems == EOF){
        	printf("EOF failure!");
        }
        else if(inputitems == 0){
        	printf("No match!");
        }
        else{
        	printf("You entered %d\n", input);
        }
    }

    capacity = BUFFSIZE/sizeof(long long int);

    if((shmemid = shmget(IPC_PRIVATE, BUFFSIZE, 0666)) < 0)
    {
        perror("shmget");
        exit(EXIT_FAILURE);
    }


    printf("segment created: %d\n", shmemid);

    if((shmbuf = (int *)shmat(shmemid, NULL, 0)) < (int *)0)
    {
        perror("shmat");
        exit(EXIT_FAILURE);
    }

    printf("segment attached at %p\n", shmbuf);

    pid = fork();

    printf("Two processes now running parent + child\n");

    if (pid > 0)
    {
       printf ("Parent about to start waiting\n");
       wait(NULL);
    }
    else if (pid == 0)
    {
       printf ("Child writing to mem\n");
       long long int a = 0;
       long long int b = 1;
       shmbuf[0] = 0;
       if(input > 0){
    	   shmbuf[1] = 1;
       }
       for (i = 2; i < input; i++){
    	   a += b;
    	   shmbuf[i]=a;
    	   if(i < input){
    		   i++;
    		   b += a;
    		   shmbuf[i] = b;
    	   }
       }

       if((shmdt(shmbuf)) < 0)
       {
          perror("shmdt");
          exit(EXIT_FAILURE);
       }
    puts("Child has detached segment");

    exit(EXIT_SUCCESS);

    }
    else
    {
       perror("fork");
       exit (EXIT_FAILURE);
    }

    printf ("Parent here - child has finished\n");
    printf ("Contents of buffer (space delimited): \n");


    for (i = 0; i < input; i++)
    {
       printf("%d ",shmbuf[i]);
    }
    printf("\n\n\n");

    if((shmdt(shmbuf)) < 0)
    {
       perror("shmdt");
       exit(EXIT_FAILURE);
    }
    puts("Parent has detached segment\n");

    shmctl(shmemid, IPC_RMID, NULL);

    printf("Parent has freed segment\n");

    return(EXIT_SUCCESS);
}

