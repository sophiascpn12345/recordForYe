#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

void *thred_func(void *arg)
{       
	int i = (int)arg;// void * is 8 byte, int 4 bytes for 64 bit cpu
	sleep(i);
	printf("%dth thread: thread id = %lu,pid = %u\n",i+1, pthread_self(), getpid());

	return NULL;
}

int main(void)
{
	pthread_t tid;
	int ret,i;

	for(i = 0; i < 5; i++){

		ret = pthread_create(&tid, NULL, thred_func, (void *)i);
		if(ret != 0){
			fprintf(stderr,"pthread_create error: %s",strerror(ret));
			exit(1);
		}
	}
	sleep(i);
	printf("In main2: thread id = %lu,pid = %u\n", pthread_self(), getpid());
	return 0;



}
