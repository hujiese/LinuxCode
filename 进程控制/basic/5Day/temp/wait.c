#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/wait.h>

int counter = 200;

int main(int argc, const char* argv[])
{
    int i;
    pid_t pid;
    for(i=0; i<5; ++i)
    {
        pid = fork();
        if(pid == 0)
        {
            break;
        }
    }

    if(i<5)
    {
        counter += 300;
        printf(" child process , pid = %d,  ppid = %d\n", getpid(), getppid());
        printf("counter = %d\n\n", counter);
    }
    else if(i == 5)
    {
        counter += 100;
        printf(" parent process, pid = %d, ppid = %d\n", getpid(), getppid());
        printf("counter = %d\n\n", counter);
        sleep(1);

        // 父进程， 回收子进程资源
        int status;
        pid_t wpid;
        while((wpid = wait(&status)) != -1 )
        {
            printf("child process died, pid = %d\n", wpid);
            if(WIFEXITED(status))
            {
                printf("process exit value: %d\n", WEXITSTATUS(status));
            }
            else if(WIFSIGNALED(status))
            {
                printf("process exit by signal: %d\n", WTERMSIG(status));
            }
        }
    }

    return 10;
}
