#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

void *thred_func(void *arg)
{
    printf("In thread: thread id = %lu,pid = %u\n", pthread_self(), getpid());

    return NULL;
}

int main(void)
{
    pthread_t tid;
    int ret;

    printf("In main1: thread id = %lu,pid = %u\n", pthread_self(), getpid());

    ret = pthread_create(&tid, NULL, thred_func, NULL);
    if(ret != 0){
	fprintf(stderr,"pthread_create error: %s",strerror(ret));
	exit(1);
    }
    sleep(1);
    printf("In main2: thread id = %lu,pid = %u\n", pthread_self(), getpid());
    return 0;



}
