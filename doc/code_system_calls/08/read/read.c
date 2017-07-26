#include <fcntl.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>

void print_10_char(char *buf) {
    int i=0;
    printf("\n\n");

    if (buf) {
        for (i=0; i < 10; i++) {
            if (buf[i] != '\0') {
                printf("%c", buf[i]);
            } else {
                break;
            }
        }
    }
}

int main ()
{

    char buf[4096] = "BUFFER";
    int bytes_read = 0, fd;

    fd = open ("/etc/passwd", O_RDONLY);

    if (fd < 0) {
        perror ("\nError opening the destination file");
        exit(1);
    } else {
        fprintf (stderr, "\nSuccessfully opened the destination file..");
    }
    bytes_read = read (fd, buf, 20);

    /* Print the first 10 bytes and the number of bytes_read */

    printf ("\nBytes Read %d", bytes_read);
    print_10_char(buf);
    return 0;
}
