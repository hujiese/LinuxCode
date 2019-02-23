#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
	int fd = open("temp-1", O_RDWR | O_CREAT, 0664);
	if(fd == -1)
	{
		perror("open");
		exit(1);
	}

	// 获取文件的flags
	int flags = fcntl(fd, F_GETFL, 0);
	// 写文件
	char *p = "hello, world!!!";
	write(fd, p, strlen(p)+1);

	// 文件flags追加属性 O_APPEND
	flags = flags | O_APPEND;
	// 设置新的flags属性
	fcntl(fd, F_SETFL, flags);

	// 写文件
	p  = "学生爱学习， 学习累了要睡觉。";
	write(fd, p, strlen(p)+1);

	close(fd);
}
