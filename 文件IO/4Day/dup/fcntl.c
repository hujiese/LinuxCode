#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>

int main()
{
	int fd = open("mytemp", O_RDWR | O_CREAT, 0664);
	if(fd == -1)
	{
		perror("open");
		exit(1);
	}

	// == dup
	int fd1 = fcntl(fd, F_DUPFD, 0);
	char* p = "hello, world!\n";
	write(fd1, p, strlen(p));
	close(fd1);
	close(fd);

	return 0;
}
