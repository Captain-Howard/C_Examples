/*
 ============================================================================
 Name        : howa831.c
 Author      : Austin Howard
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#define NUM_THREADS 1
#define BUFFER 1024

pthread_t tid[NUM_THREADS];

int prime_num[BUFFER];
int ret1, low, high, i, flag, n, a, b;

void* doSomething(void *arg){
	pthread_t id = pthread_self();
	low = 1;
	n = 0;
	a = 0;
	b = 1;
	if(pthread_equal(id, tid[0])){

		printf("\n Thread[1] done\n");
		ret1 = 10;

		//Here I will create the fibonacci sequence for n-amount
		prime_num[n] = a;
		n++;
		prime_num[n] = b;
		for(n = 2; n < high; n++){
			a += b;
			prime_num[n] = a;
			n++;
			if(n < high){
				b += a;
				prime_num[n] = b;
			}
		}

		pthread_exit(&ret1);
	}
	return NULL;
}

int main(int argc, char *argv[]){
	if(argc != 2 ){
		printf("Please provide a number to count to next time.");
		exit(1);
	}
	high = atoi(argv[1]);
	int j = 0;
	int err;
	int *ptr[NUM_THREADS];

	while(j < NUM_THREADS){
		err = pthread_create(&(tid[j]), NULL, &doSomething, NULL);
		if(err != 0){
			printf("\nCan't create thread: [%d]", err);
		}
		j++;
	}
	for(j = 0; j < NUM_THREADS; j++){
		pthread_join(tid[i], (void**)&(ptr[j]));
	}
	printf("\n All Threads Run\n");

	printf("\nFibonacci Sequence: \n");
	for(j = 0; j < high; j++){
		printf("[%d]\t%d\n", j+1, prime_num[j]);
	}
	return 0;
}
