#include "vector.h"

#include <stdlib.h>
#include <stdio.h>

int main() {
	Vector vec;
	char *str;
	vector_init(&vec, INT);
	vector_set_int(&vec, 1024, 100);
	str = vector_to_string(&vec);
	printf("%s\n", str);

	free(str);
	return (0);
}
