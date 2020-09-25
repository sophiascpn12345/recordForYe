#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

int var = 100;

void *thred_func(void *arg)
{       

	var =200;
	printf("thread\n");
	return NULL;
}

int main(void)
{
	printf("at first var = %d\n",var);

	pthread_t tid;

        pthread_create(&tid, NULL, thred_func, NULL);
	sleep(1);
	printf("after pthread_create,var = %d",var);
	return 0;



}
