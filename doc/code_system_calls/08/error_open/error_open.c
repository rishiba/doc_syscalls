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
        int errsv = errno;      // We need to copy the errno just after the system call.
        printf("\nError number is %d", errsv);
        
        if (errsv == ENOENT) {
            printf("\nFile does not exist. Check if the file is there.");
        }

        /*
         * Use library function to get the error msg.
         */
        char *errmsg = strerror(errsv);
        printf ("\nError is: %s\n", errmsg);
        exit(1);
    } else {
        printf ("\nSuccessfully opened the destination file. Closing it.\n");
        close(fd);
    }
    return 0;
}
