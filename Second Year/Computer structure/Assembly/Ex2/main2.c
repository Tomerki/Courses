#include <stdio.h>
int even (int num, int i);

int go (int A[10]);


int main()
{
    int array[10] = {2,1,2,1,1,1,1,1,1,1};
    int answer = go(array);
    printf("this is you answer: %d\n", answer);

    return 0;
}