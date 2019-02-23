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

    pid_t pid = fork();
    if(pid == -1)
    {
        perror("fork error");
        exit(1);
    }

    // 父进程　写　，　关闭读操作
    if(pid > 0)
    {
        sleep(1);
        close(fd[0]);
        char* p = "hell, world\n";
        write(fd[1], p, strlen(p)+1);
        close(fd[1]);

        wait(NULL);
    }
    else if(pid == 0)
    {
        close(fd[1]);
        char buf[1024];
        read(fd[0], buf, sizeof(buf));
        printf("buf = %s\n", buf);
        close(fd[0]);
    }

    return 0;
}
