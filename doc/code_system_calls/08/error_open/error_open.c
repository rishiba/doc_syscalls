#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>


int main ()
{

    int fd;

    fd = open ("NON_EXISTENT_FILE", O_RDONLY);

    if (fd < 0) {
        printf ("Error is %s", strerror (errno));
        perror("Got error as ");
        printf("\nError number is %d", errno);
        exit(1);
    } else {
        fprintf (stderr, "\nSuccessfully opened the destination file. Closing it.");
        close(fd);
    }
    return 0;
}
