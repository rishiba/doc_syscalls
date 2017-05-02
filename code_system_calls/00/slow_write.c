/*
 * In this code we will open the /etc/passwd file and copy the file 1000 times
 * to the output file. We will copy it 1000 times so that we have a good amount
 * data to run our test on.
 */

#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main ()
{
    char *src_file = "src_file";
    char *dest_file = "copied_file.txt";

    int dest_fd, src_fd, read_byte, write_byte;
    char read_buf[1];

    dest_fd = open (dest_file, O_WRONLY|O_CREAT);

    if (dest_fd < 0) {
        fprintf (stderr, "Error Opening the destination file.");
        exit(1);
    } else {
        fprintf (stderr, "Successfully opened the destination file..");
    }

    src_fd = open (src_file, O_RDONLY);

    if (src_fd < 0) {
        fprintf (stderr, "Error Opening the source file.");
        exit(1);
    } else {
        fprintf (stderr, "Successfully opened the source file.");
    }


    /*
     * We will start the copy process byte by byte
     */

    while (1) {
        read_byte = read (src_fd, read_buf, 1);
        if (read_byte == 0) {
            fprintf(stdout, "Reached the EOF for src file");
            break;
        }
        write_byte = write (dest_fd, read_buf, 1);

        if (write_byte < 0) {
            perror ("Error Writing File");
            exit (1);
        }
    }

    close(src_fd);
    close(dest_fd);

    return 0;
}
