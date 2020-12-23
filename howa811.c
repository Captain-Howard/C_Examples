/*
 ============================================================================
 Name        : howa811.c
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
#define NUM_THREADS 10
pthread_t tid[NUM_THREADS];
int ret1;

void* doSomething(void *arg){
	pthread_t id = pthread_self();

	if(pthread_equal(id, tid[0])){
		printf("\n Thread[1] done\n");
		ret1 = 10;
		pthread_exit(&ret1);
	}
	else if(pthread_equal(id, tid[1])){
		printf("\n Thread[2] done\n");
		ret1 = 20;
		pthread_exit(&ret1);
	}
	else if(pthread_equal(id, tid[2])){
		printf("\n Thread[3] done\n");
		ret1 = 30;
		pthread_exit(&ret1);
	}
	else if(pthread_equal(id, tid[3])){
		printf("\n Thread[4] done\n");
		ret1 = 40;
		pthread_exit(&ret1);
	}
	else if(pthread_equal(id, tid[4])){
		printf("\n Thread[5] done\n");
		ret1 = 50;
		pthread_exit(&ret1);
	}
	else if(pthread_equal(id, tid[5])){
		printf("\n Thread[6] done\n");
		ret1 = 60;
		pthread_exit(&ret1);
	}
	else if(pthread_equal(id, tid[6])){
		printf("\n Thread[7] done\n");
		ret1 = 70;
		pthread_exit(&ret1);
	}
	else if(pthread_equal(id, tid[7])){
		printf("\n Thread[8] done\n");
		ret1 = 80;
		pthread_exit(&ret1);
	}
	else if(pthread_equal(id, tid[8])){
		printf("\n Thread[9] done\n");
		ret1 = 90;
		pthread_exit(&ret1);
	}
	else{
		printf("\n Thread[10] done\n");
		ret1 = 100;
		pthread_exit(&ret1);
	}
	return NULL;
}

int main(void){
	int i = 0;
	int err;
	int *ptr[NUM_THREADS];

	while(i < NUM_THREADS){
		err = pthread_create(&(tid[i]), NULL, &doSomething, NULL);
		if(err != 0){
			printf("\nCan't create thread: [%d]", err);
		}
		else{
			//printf("\n Thread created successfully\n");
		}
		i++;
	}
	for(i = 0; i < NUM_THREADS; i++){
		pthread_join(tid[i], (void**)&(ptr[i]));
	}
	printf("\n All Threads Run\n");

	return 0;
}
