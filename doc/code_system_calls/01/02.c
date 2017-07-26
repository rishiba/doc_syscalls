#include <fcntl.h>
#include <string.h>

int main ()
{
    char filename[] = "non_existent_file";
    int fd;
    fd = open (filename, O_CREAT|O_WRONLY);

    fd = write (fd, filename, strlen(filename));
    close (fd);
    unlink (filename);
    return 0;
}
