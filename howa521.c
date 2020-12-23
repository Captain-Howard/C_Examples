/*
 ============================================================================
 Name        : howa521.c
 Author      : Austin Howard
 Version     :
 Copyright   : Don't steal my stuff.
 Description : Hello World in C, Ansi-style
 ============================================================================
 */
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#define MAX 80

int main(int argc, char* argv[])
{

	/*==========================
	 *    ERROR CHECKING THE
	 *      ENTERED VALUES
	 *==========================
	 */
	if(argc < 2){
		printf("\nPlease enter a second parameter!\n");
	}

	else if(argc > 2){
		printf( "\nPlease reformat your arguments: \n"
				"Instead of: \n"
				"		%s", argv[0]);
		for(int i = 1; i < argc; i++){
			printf(" %s", argv[i]);
		}
		printf("\n\nOnly use two parameters, like this: \n"
		    	"		%s %s\n", argv[0], argv[1]);
	}

	else{
		   int children[2], nbytes;
		   pid_t pid;
		   char typed[MAX];
		   char readbuffer[MAX];
		   int n = 2;
		   long int a = 0;
		   long int b = 1;
		   long int c;
		   pipe(children);
		   //---------------------//
		   //  COPY ARGV STRING   //
		   //     INTO CUSTOM     //
		   //---------------------//
		   strcpy(typed, argv[1]);
		   long int input = atoi(typed); //Changing string into long int

		   if(input <= 0){
			   printf("\nPlease enter a positive integer above zero!\n");
		   }
		   else{

			   //---------------------//
			   // ERROR CHECKING AND  //
			   //   CHILD CREATION    //
			   //---------------------//
			   if ((pid = fork()) < 0){

			      perror("Fork Failed");
			      exit(EXIT_FAILURE);
			   }

			   /* child process */
			   if (pid == 0){

				   printf("\nThe Fibonacci Sequence was: \n"
						   "No.\tVal.\n1\t0\n2\t1\n");
				  /*=================================
				   *      FIBONACCI SEQUENCE
				   *=================================
				   */
				  while(n < input){
					  a += b;
					  c = a;
					  n++;
					  printf("%d\t%ld\n", n, c);
					  if(n >= input){
						  break;
					  }
					  b += a;
					  c = b;
					  n++;
					  printf("%d\t%ld\n", n, c);
				  }
				  long int character = (long) getpid();
				  char cpid[MAX];

				  sprintf(cpid, "%ld", character);

				  //creating a pipe to send the pid to the parent
				  close(children[0]);

				  //Send the PID to the parent
				  write(children[1], cpid, (strlen(cpid)+1));

			   }

			   /*     parent to the child process
			    *
			    * ==================================
			    *   PARENT SCRIPTS YOU WANT TO RUN
			    * ==================================
			    *
			    */
			   else
			   {
			      wait(NULL);

			      //creating the parent end of the pipe to receive the child pid
			      close(children[1]);

			      //reading children
			      nbytes = read(children[0], readbuffer, sizeof(readbuffer));

			      printf("\nProc.\tChild\tParent\n");
			      printf("ID\tID\tID\n");
			      printf("%ld\t%s\t%ld\n", (long)getpid(), readbuffer, (long)getppid());

			   }
		}



		   }

   return EXIT_SUCCESS;
}


