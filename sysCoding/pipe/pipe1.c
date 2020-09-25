#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

void do_wait(int signo)
{
    pid_t pid;
    int status;
    while((pid=waitpid(0,NULL,WNOHANG)) >0){
        if(WIFEXITED(status))
	    printf("child exit with %d\n", WEXITSTATUS(status));
	else if(WIFSIGNALED(status))
	    printf("child killed by %d\n",WTERMSIG(status));
    }
}


int main(void)
{
    pid_t pid;
    int fd[2];
    pipe(fd);
    pid = fork();

    if(pid ==0){
        close(fd[1]);
	dup2(fd[0],STDIN_FILENO);
	execlp("wc","wc","-l",NULL);
    } else {
	signal(SIGCHLD, do_wait);
        close(fd[0]);
	dup2(fd[1],STDOUT_FILENO);
	execlp("ls","ls",NULL);
    }

    return 0;
}
