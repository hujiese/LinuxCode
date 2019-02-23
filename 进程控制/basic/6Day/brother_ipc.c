#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, const char* argv[])
{
    int fd[2];
    int ret  = pipe(fd);
    if(ret == -1)
    {
        perror("pipe error");
        exit(1);
    }

    printf("fd[0] = %d\n", fd[0]);
    printf("fd[1] = %d\n", fd[1]);

    int i = 0;
    int num = 2;
    for(; i<num; ++i)
    {
        pid_t pid = fork();
        if(pid == 0)
        {
            break;
        }
    }

    // parent recyle child pcb
    if(i == num)
    {
        close(fd[0]);
        close(fd[1]);

        // ｒｅｃｙｌｅ
        pid_t wpid;
        while( (wpid = waitpid(-1, NULL, WNOHANG)) != -1 )
        {
            if(wpid == 0)
            {
                continue;
            }
            printf("died child pid = %d\n", wpid);
        }
    }
    else if(i == 0)
    {
        // ps aux
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        execlp("ps", "ps", "aux", NULL);
    }
    else if(i == 1)
    {
        // grep bash
        close(fd[1]);
        dup2(fd[0], STDIN_FILENO);
        execlp("grep", "grep", "bash", NULL);
    }

    return 0;
}
