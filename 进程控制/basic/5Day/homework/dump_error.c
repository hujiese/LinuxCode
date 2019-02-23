#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>


int main(int argc, const char* argv[])
{
    char* p = "hello, world......";

    p[2] = '9';
    printf("%s\n", p);

    return 0;
}
