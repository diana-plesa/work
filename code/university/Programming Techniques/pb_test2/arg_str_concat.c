#include <stdio.h>
#include <stdarg.h>

/*Să se scrie o funcție char *concat(int n,...) care primește un număr de șiruri de caractere și apoi
șirurile propriu-zise. Funcția va concatena într-un nou șir, alocat dinamic, conținuturile tuturor șirurilor date, cu câte
un spațiu între ele și va returna acest șir.
Exemplu: concat(3,”Ion”,”si”,”Ana”) => “Ion si Ana”*/

char *concat(int n, ...)
{
    va_list ap;
    va_start(ap, n);

    for (int i = 0; i < n; i++)
    {
        va_get(ap, char *)
    }
}

int main()
{
    return 0;
}