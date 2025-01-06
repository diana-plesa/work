#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void write_text()
{
    FILE *f = fopen("diablo.txt", "w");

    if (f == NULL)
    {
        perror("Error open file\n");
        exit(-1);
    }

    fputs("toast", f);
    if (fclose(f) != 0)
    {
        perror("Error close file\n");
        exit(-1);
    }
}

void read_text()
{
    FILE *f = fopen("diablo.txt", "r");

    if (f == NULL)
    {
        perror("Error open file for read\n");
        exit(-1);
    }
    char string[10];

    fgets(string, 10, f);
    string[strcspn(string, "\n")] = '\0';

    printf("%s\n",string);

    if (fclose(f) != 0)
    {
        perror("Error close file\n");
        exit(-1);
    }
}

void write_binary()
{
    FILE *g = fopen("diablo.bin", "wb");

    if (g == NULL)
    {
        perror("Error open binary write\n");
        exit(-1);
    }

    char string[10] = "buddah";
    fwrite(string, 10, 1, g);

    fclose(g);

}

void read_binary()
{
    FILE *g = fopen("diablo.bin", "rb");

    char string[10];
    fread(string, 10, 1, g);
    printf("%s\n", string);
    fclose(g);
}

int main()
{
    write_text();
    read_text();
    write_binary();
    read_binary();
    return 0;
}