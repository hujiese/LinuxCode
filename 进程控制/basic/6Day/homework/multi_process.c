#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

int main(int argc, const char* argv[])
{
    int num = 3;
    int i = 0;
    pid_t pid;

    for(i=0; i<num; ++i)
    {
        pid = fork();
        if(pid == 0)
        {
            break;
        }
    }

    if(i == 0)
    {
        execlp("ps", "ps", "aux", NULL);
        perror("execlp ps");
        exit(1);
    }
    else if(i == 1)
    {
        execl("/home/kevin/test/app", "app", NULL);
        perror("execl app");
        exit(1);
    }
    else if(i == 2)
    {
        execl("./error", "error", NULL);
        perror("execl error");
        exit(1);
    }
    else if(i == num)
    {
        // 回收
        int status;
        pid_t wpid;
        while( (wpid = waitpid(-1, &status, WNOHANG)) != -1 )
        {
            printf(" ----- child died pid = %d\n", wpid);
            if(WIFEXITED(status))
            {
                printf("return value %d\n", WEXITSTATUS(status));
            }
            else if(WIFSIGNALED(status))
            {
                printf("died by signal: %d\n", WTERMSIG(status));
            }
        }
    }
    return 0;
}
