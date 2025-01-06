#include <stdio.h>

int main()
{
    char v[4];
    FILE *f;
    f = fopen("t.txt", "r");
    fgets(v, 4, f);
    printf("%s", v);
    fclose(f);
    return 0;
}