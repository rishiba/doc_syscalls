#include <fcntl.h>
#include <unistd.h>

int main ()
{
    write (1, "Hello World", 11);
    return 0;
}
