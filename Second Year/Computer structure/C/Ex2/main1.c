#include <stdio.h>
#include "ex2.h"

int print_magnitude(magnitude x){
    unsigned int mask = 0x7FFFFFFF, sign_mask = 0x80000000;
    int sign = (sign_mask & x) > 0 ? -1:1;
    return (int) ((x & mask) * sign);
}

int main()
{
    printf("%d\n", multi(10, 5));
    printf("%d\n", add(-1, 4));
    printf("%d\n", add(-6, 1));
    printf("%d\n", sub(8, -3));
    printf("%d\n", equal(4, 4));
    printf("%d\n", greater(4, 4));
    printf("%d\n\n", multi(1, add(3, 5)));
    return 0;
}