#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int n, flag = 0;

void sys_err(char *str)
{
    perror(str);
    exit(1);
}

void do_sig_child(int num)
{
    printf("i am child %d\t%d\n",getpid(), n);
    n += 2;
    flag = 1;
    //sleep(1);
}

void do_sig_parent(int num)
{
    printf("i am parent %d\t%d\n",getpid(), n);
    n += 2;
    flag = 1;
   // sleep(1);
}

int main(void)
{
    pid_t pid;
    struct sigaction act;

    if((pid = fork()) < 0 )
        sys_err("fork");
    else if (pid >0){
        n = 1;
	sleep(1);
	act.sa_handler = do_sig_parent;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	sigaction(SIGUSR2, &act, NULL);    //注册自己的信号捕捉函数   父使用SIGUSR2信号
       
	do_sig_parent(0);

	while(1){
	    /* wait for signal*/
	    if(flag == 1){               //父进程数数完成
	        kill(pid, SIGUSR1);
		flag = 0;                //标志已经给子进程发送完信号
	    }
	}


    }else if(pid ==0){
        n=2;
	act.sa_handler = do_sig_child;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	sigaction(SIGUSR1, &act, NULL);    //注册自己的信号捕捉函数   父进程数数完发送SIGUSR1信号给子进程
	
	while(1){
	    /* wait for signal*/
	    if(flag == 1){               //子进程数数完成
	        kill(getppid(), SIGUSR2);
		flag = 0;                //标志已经给父进程发送完信号
	    }
	}

    }
}
