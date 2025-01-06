#include <stdio.h>
#include <string.h>

int main()
{
    FILE *f = fopen("testez.txt", "r");

    int n, x;
    char s[100];
    fscanf(f, "%d", &n);

    while (n > 0)
    {
        fscanf(f, "%d", &x);
        fgetc(f);
        fgets(s, 100, f);
        s[strcspn(s, "\n")] = '\0';

        printf("%d %s\n", x, s);
        n--;
    }

    fclose(f);
    return 0;
}