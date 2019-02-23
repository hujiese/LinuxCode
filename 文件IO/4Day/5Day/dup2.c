#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
	int fd = open("temp", O_RDWR | O_CREAT | O_APPEND, 0664);
	if(fd == -1)
	{
		perror("open");
		exit(1);
	}

	int fd2 = open("temp1", O_RDWR | O_CREAT | O_APPEND, 0664);
	if(fd2 == -1)
	{
		perror("open-2");
		exit(1);
	}
	// 复制文件描述符
	dup2(fd, fd2);
	// 写文件
	char *p = "change the world by programing......";
	write(fd2, p, strlen(p)+1);
	close(fd2);

	// 读文件
	char buf[64]={0};
	lseek(fd, 0, SEEK_SET);
	read(fd, buf, sizeof(buf));
	printf("buf = %s\n", buf);
	close(fd);
}
