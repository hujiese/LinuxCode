#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>

int main(int argc, const char* argv[])
{
    // read
    int fd = open("english.txt", O_RDONLY);
    if(fd == -1)
    {
        perror("read open error");
        exit(1);
    }

    // write
    int fd1 = open("copy", O_WRONLY | O_CREAT, 0664);
    if(fd1 == -1)
    {
        perror("write open error");
        exit(1);
    }

    // read english.txt
    char buf[4096];
    int len = read(fd, buf, sizeof(buf));

    while(len)
    {
        // 读出的数据写到另一个文件ｃｏｐｙ
        int ret = write(fd1, buf, len);
        printf("write bytes: %d\n", ret);
        len = read(fd, buf, sizeof(buf));
        if(len == -1)
        {
            perror("read  error");
            exit(1);
        }
    }

    close(fd);
    close(fd1);

    return 0;
}
