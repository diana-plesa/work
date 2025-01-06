#include <stdio.h>
#include <time.h>
#include "is_odd.h"

int main()
{
    clock_t end, start;
    start = clock();
    int x;
    x = is_odd(7);
    printf("%d", x);
    end = clock();

    printf("\n%ld\n", end - start); //clocks per sec
    return 0;
}