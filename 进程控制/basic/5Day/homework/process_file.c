#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>

int main(int argc, const char* argv[])
{
    int fd = open("temp", O_CREAT | O_RDWR, 0664);
    if(fd == -1)
    {
        perror("open error");
        exit(1);
    }
    pid_t pid = fork();
    if(pid == -1)
    {
        perror("fork error");
        exit(1);
    }

    if(pid > 0)
    {
        char* p = "近期，微软向Linux开发人员伸出了橄榄枝，希望Linux开发人员能够转移到Windows 10平台上进行开发。";
        write(fd, p, strlen(p)+1);
    }
    else if(pid == 0)
    {
        // 睡1s保证父进程已经完成了文件的写操作
        sleep(1);
        char buf[1024];
        lseek(fd, 0, SEEK_SET);
        int len = read(fd, buf, sizeof(buf));
        printf("%s\n", buf);
    }

    close(fd);
    return 0;
}
