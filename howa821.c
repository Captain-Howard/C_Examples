/*
 ============================================================================
 Name        : howa821.c
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
int ret1, low, high, i, flag, n;

void* doSomething(void *arg){
	pthread_t id = pthread_self();
	low = 1;
	n = 0;
	if(pthread_equal(id, tid[0])){

		printf("\n Thread[1] done\n");
		ret1 = 10;

		while(low <= high){
			flag = 0;
			for(i = 2; i <= low/2; i++){
				if(low % i == 0){
					flag = 1;
					break;
				}
			}

			if(flag == 0){
				prime_num[n] = low;
				n++;
			}
			low++;
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

	printf("\nPrime Numbers: \n");
	for(j = 0; j < n; j++){
		printf("%d\n", prime_num[j]);
	}
	return 0;
}
