#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

int main(int argc, const char* argv[])
{
    int i = 0;
    int number = 3;
    pid_t pid;

    for(i = 0; i<number; ++i)
    {
        pid = fork();
        if(pid == 0)
        {
            break;
        }
    }

    // 父进程
    if(i == number)
    {
        sleep(2);
        // 回收子进程
        pid_t wpid;
        int status;
        while( (wpid = waitpid(0, &status, WNOHANG)) != -1 )
        {
            if(wpid == 0)
            {
                continue;
            }
            printf("child pid = %d\n", wpid);
            if(WIFEXITED(status))
            {
                printf("return number: %d\n", WEXITSTATUS(status));
            }
            else if(WIFSIGNALED(status))
            {
                printf("exit by signal: %d\n", WTERMSIG(status));
            }
        }
    }
    else if(i == 0)
    {
        execl("/home/kevin/test/app", "app", NULL);
    }
    else if(i == 1)
    {
        execl("./error", "error", NULL);
    }
    else if(i == 2)
    {
        execlp("ps", "ps", "aux", NULL);
    }

    printf("over......\n");
    return 0;
}
