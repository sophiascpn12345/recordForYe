#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>

void mydaemond(void)
{
    
    pid_t pid;
   

    pid = fork();
    if(pid > 0){
        exit(1);
    }

    setsid();

    int ret = chdir("/home/ye/");
    if(ret == -1){
        perror("child error");
	exit(1);
    }
    umask(0022);

    //close(fd[0]);//stdin
    close(STDIN_FILENO);
    open("/dev/null",O_RDWR);
    dup2(0,STDOUT_FILENO);
    dup2(0,STDERR_FILENO);

}

int main(void)
{
    mydaemond();
    while (1){
     //信号捕捉后自杀退出
    }

    return 0;
}
