#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

/*Definiți o funcție cu număr variabil de argumente, denumita tiparire, care citește din fișierul
text CUVINTE.TXT, pe rând argumentele necesare:
- un număr n
- n perechi, fiecare pereche fiind compusă dintr-un număr întreg x și un șir de caractere.
Pentru fiecare pereche din cele n, funcția va afișa în fișierul text COMPUSE.TXT, pe rânduri
diferite, fiecare cuvânt, precum și litera de pe pozițiea x din cuvânt. În cazul în care x e mai mare
ca lungimea cuvântului, se va afișa ultima literă a cuvântului în loc de litera de pe poziția x. */

void tiparire(int n, ...)
{
    va_list arg_list;
    int x;
    char word[100];
    va_start(arg_list, n);

    FILE *f = fopen("COMPUSE.TXT", "w");

    if (f == NULL)
    {
        perror("Eroare deschidere compuse.txt");
        exit(-1);
    }

    while (n > 0)
    {
        x = va_arg(arg_list, int);
        strcpy(word, va_arg(arg_list, char*));

        fprintf(f, "%s ", word);

        if (x >= strlen(word))
        {
            fprintf(f, "%c\n", word[strlen(word) - 1]);
        }
        else 
        {
            fprintf(f, "%c\n", word[x]);
        }

        n--;
    }

    va_end(arg_list);
    char file_word[100];
    int file_x;
    int file_n;

    FILE *g = fopen("CUVINTE.TXT", "r");

    if (g == NULL)
    {
        perror("eroare deschidere fisier cuvinte.txt");
        exit(-1);
    }

    fscanf(g, "%d", &file_n);

    while (file_n > 0)
    {
        fscanf(g, "%d", &file_x);
        fgetc(g);
        fgets(file_word, 100, g);
        file_word[strcspn(file_word, "\n")] = '\0';

        fprintf(f, "%s ", file_word);

        if (file_x < strlen(file_word))
        {
            fprintf(f, "%c\n", file_word[file_x]);
        }
        else 
        {
            fprintf(f, "%c\n", file_word[strlen(file_word) - 1]);
        }

        file_n--;

    } 
    
    if (fclose(g) != 0)
    {
        perror("Eroare inchidere fisier cuvinte.txt");
        exit(-1);
    }

    if (fclose(f) != 0)
    {
        perror("Eroare inchidere fisier compuse.txt");
        exit(-1);
    }
}

int main()
{
    tiparire(3, 1, "ana", 0, "are", 7, "mere");
    return 0;
}