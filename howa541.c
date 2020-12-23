/*
 ============================================================================
 Name        : howa541.c
 Author      : Austin Howard
 Version     : v1.0
 Copyright   : Don't touch my stuff!!!
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

//MAIN FUNCTION DEFINITIONS
int a = 0;
void forker(int nprocesses);

int main(void) {

	forker(100);

	//This is at the end of the while loop saying that we've successfully
	//	made all of the 1st generation children
	printf("\nYou've created %d\n\n", a);
	return EXIT_SUCCESS;
}


void forker(int nprocesses){
	pid_t pid;
	a++;
	if(nprocesses > 0){

		if((pid = fork()) < 0){
			perror("fork");
		}

		else if(pid == 0){
			//child stuff here
			printf("Childs PID:\t%d\n", getpid());
			printf("Parent PID:\t%d\n", getppid());
			printf("Childs num:\t%d\n", 11-nprocesses);
			printf("----------------\n");
		}

		else{
			//parent
			forker(nprocesses-1);
		}
	}
}
