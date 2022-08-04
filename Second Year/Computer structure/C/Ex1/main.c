#include <stdio.h>
#include "ex1.h"

int main() {

	printf("%d\n", is_big_endian());
    merge_bytes(0x89ABCDEF12893456, 0x76543210ABCDEF19);

	printf("0x%lx\n", merge_bytes(0x89ABCDEF12893456, 0x76543210ABCDEF19));

	printf("0x%lx\n", put_byte(0x12345678CDEF3456, 0xAB, 4));
	printf("0x%lx\n", put_byte(0x12345678CDEF3456, 0xAB, 0));

	return 0;
}