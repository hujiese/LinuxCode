#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>


int main(int argc, const char* argv[])
{
    pid_t pid;

    pid = fork();
    if(pid == -1)
    {
        perror("fork error");
        exit(1);
    }

    if(pid > 0)
    {
        printf("i am parent process, pid = %d, ppid = %d\n", getpid(), getppid());
    }
    else if(pid == 0)
    {
        printf("i am child process, pid = %d, ppid = %d\n", getpid(), getppid());
        sleep(1);
    }


    for(int i=0; i<5; ++i)
    {
        printf("i = %d\n", i);
    }

    return 0;
}
