#include <stdio.h>
#include <stdlib.h>


int main () {

	div_t result = div(99, 99);
	int x = my_div();

	printf ("\n\nQuotient %d Remainder %d", result.quot, result.rem);
	return 0;
}
