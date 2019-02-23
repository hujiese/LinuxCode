#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>


int main(int argc, const char* argv[])
{
    pid_t pid;
    
    pid = fork();
    if(pid == -1)
    {
        perror("fork error");
        exit(1);
    }

    if(pid == 0)
    {
///        execl("/home/kevin/app",  "app", NULL);
        char* args[] = {"ls", "-lah", NULL};
        execv("/bin/ls", args);
//        execl("ls", "ls", "-lah", NULL);
//        execlp("/home/kevin/test/app", "app", NULL);
//        execlp("ps", "ps", "aux", NULL);
        perror("execl error");
        exit(1);
    }

    printf("bye bye......\n");
    sleep(1);

    return 0;
}
