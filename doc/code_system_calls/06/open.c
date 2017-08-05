#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>


int main ()
{
    int fd = open ("/etc/passwd", O_RDONLY);
    close(fd);
    return 0;
}
