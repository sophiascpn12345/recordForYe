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

	pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
	pthread_t tid;
	int n=5,i;

	if(argc == 2)
		n = atoi(argv[1]);

	for(i = 0; i < n; i++){
		pthread_create(&tid, NULL, thred_func, (void *)i);
	}
	printf("I am main,and i am not a process, i am a thread\n"
		       	"main thred id  =  %lu\n", pthread_self());
	pthread_exit(NULL);
	return 0;



}
