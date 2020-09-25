#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct {
    char ch;
    int var;
    char str[64];
} exit_t;

void *thred_func(void *arg)
{
        exit_t *retval = (exit_t *)malloc(sizeof(exit_t));

        retval->ch = 'm';
        retval->var = 200;
        strcpy(retval->str, "my thread\n");

	pthread_exit((void*)retval);
}


int main(void)
{
	pthread_t tid;
	int ret;
        exit_t *retval;

	
	printf("In main 1: thread id = %lu,pid = %u\n", pthread_self(), getpid());
	
	ret = pthread_create(&tid, NULL, thred_func, NULL);
	if(ret != 0){
		fprintf(stderr,"pthread_create error: %s\n",strerror(ret));
		exit(1);
	}
        pthread_join(tid, (void**)&retval);
	printf("ch = %c, var = %d, str = %s\n",retval->ch,retval->var,retval->str);

	free(retval);
	pthread_exit((void*)1);


}
