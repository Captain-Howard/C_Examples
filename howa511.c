/*
 * lab517.c
 *
 *  Created on: Feb 9, 2017
 *      Author: tom
 */
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc, char* argv[])
{
   pid_t pid;
   int n = 0;
   printf("\nLevel\tProc.\tParent\n");
   printf("No.\tID\tID\n");


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

	  n++; //Increase the level No.

	   //---------------------//
	   // ERROR CHECKING AND  //
	   // GRANDCHILD CREATION //
	   //---------------------//
	  if ((pid = fork()) < 0)
      {
         perror("Fork Failed");
         exit(EXIT_FAILURE);
      }

      /* grand-child process */
      else if (pid == 0){

    	 n++; //Increase the level No.

    	 //---------------------//
    	 // ERROR CHECKING AND  //
    	 //  GREAT GRANDCHILD   //
    	 //     CONCEPTION      //
    	 //---------------------//
         if ((pid = fork()) < 0){
            perror("Fork Failed");
            exit(EXIT_FAILURE);
         }

         /* great grand-child process
          *
          * =======================================
          *  GREAT GRAND-CHILD SCRIPTS YOU WANT TO
          *                   RUN
          * =======================================
          */

         else if (pid == 0){

        	 n++; //Increase the level No.
        	 printf("%d\t%ld\t%ld\n", n, (long)getpid(), (long)getppid());
         }

         /* parent to the great grand-child process
          *
          * =======================================
          *   GRAND CHILD SCRIPTS YOU WANT TO RUN
          * =======================================
          *adbu
          */
         else {
            wait(NULL);
            printf("%d\t%ld\t%ld\n", n, (long)getpid(), (long)getppid());
         }
      }
	 /*   parent to the grand-child process
	  *
	  * =======================================
	  *      CHILD SCRIPTS YOU WANT TO RUN
	  * =======================================
	  *
	  */
      else{
         wait(NULL);
         printf("%d\t%ld\t%ld\n", n, (long)getpid(), (long)getppid());
      }
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
      printf("%d\t%ld\t%ld\n", n, (long)getpid(), (long)getppid());
   }
   return EXIT_SUCCESS;
}


