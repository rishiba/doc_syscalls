#include <stdio.h>
#include <stdlib.h>


int main () {

    div_t result = div(99, 99);
    int x = mydiv();

    printf ("\n\nQuotient %d Remainder %d", result.quot, result.rem);
    printf ("\nValue returned by mydiv is %d\n\n", x);
    return 0;
}
