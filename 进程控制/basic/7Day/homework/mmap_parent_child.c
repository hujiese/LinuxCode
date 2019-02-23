#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/wait.h>


int main(int argc, char *argv[])
{

	int fd = open("temp", O_RDWR | O_CREAT, 0664);

	// 文件拓展
	ftruncate(fd, 10240);
	// 得到文件长度
	int len = lseek(fd, 0, SEEK_END);
	void* ptr = mmap(NULL, len, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	close(fd);

	// 判断返回值
	if(ptr == MAP_FAILED)
	{
		perror("mmap");
		exit(1);
	}


	// 创建子进程
	pid_t pid = fork();

	if(pid > 0)
	{
		// parent
		// 写
		strcpy(ptr, "你是我的儿子吗？？？？");

		wait(NULL);
	}
	else if(pid == 0)
	{
		// child
		// 保证儿子能读到数据， 睡一会儿
		sleep(1);
		printf("buf = %s\n", (char*)ptr);
	}

	// 释放内存映射区
	int r = munmap(ptr, 1024);
	if(r == -1)
	{
		perror("munmap");
		exit(1);
	}


	return 0;
}




