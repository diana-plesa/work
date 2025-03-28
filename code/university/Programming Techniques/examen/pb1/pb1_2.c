#include <stdio.h>
#include <stdlib.h>

/*Se citeste din fișierul text N.TXT un numar natural n si apoi n numere naturale ordonate strict
crescator reprezentand valorile a n bancnote.
Se citeste apoi o suma de bani s si se cere sa se plateasca in toate modurile posibile suma s cu
bancnote de valorile precizate. Se presupune ca avem la dispozitie oricate bancnote de fiecare
valoare. Să se scrie toate rezultatele obținute în fișierul text REZULTATE.TXT.
Ex:
n=4
valorile bancnotelor: 1 5 10 50
s=100
Se vor obtine solutii de forma:
2*50
5*10 1*50
10*10
2*5 4*10 1*50
...
35*1 1*5 1*10 1*50
...
95*1 1*5
*/

void print(int step, int *sol, int sum)
{
/*    FILE *g = fopen("REZULTATE.TXT", "w");

    if (g == NULL)
    {
        perror("Eroare deschidere fisier rezultate.txt");
        exit(-1);
    }
*/
    int nb = 1, i = 0;
    printf("%d = ", sum);
    for (i = 0; i < step; i++)
    {
        if (sol[i] == sol[i + 1])
        {
            nb++;
        }
        else 
        {
            printf("%d * %d  ", nb, sol[i]);
            nb = 1;
        }
    }

    printf("%d * %d", nb, sol[i]);

    printf("\n");

/*
    if (fclose(g) != 0)
    {
        perror("Eroare inchidere fisier rezultate.txt");
        exit(-1);
    }
*/
}

int solution(int step, int *sol, int sum)
{
    int s = 0;
    for (int i = 0; i <= step; i++)
    {
        s = s + sol[i];
    }

    return s == sum;
}

int valid(int step, int *sol, int sum)
{
    int s = 0;
    for (int i = 0; i <= step; i++)
    {
        s = s + sol[i];

        if (i > 0 && sol[i - 1] > sol[i])
            return 0;
    }

    return s <= sum;
}

void back(int step, int *sol, int n, int sum, int *money)
{
    for (int i = 0; i < n; i++)
    {
        sol[step] = money[i];

        if (valid(step, sol, sum))
        {
            if (solution(step, sol, sum))
                print(step, sol, sum);
            else 
                back(step + 1, sol, n, sum, money);
        }
    }
}

int main()
{
/*    FILE *f;
    f = fopen("N.TXT", "r");

    if (f == NULL)
    {
        perror("Eroare deschidere fisier N.TXT");
        exit(-1);
    }

    int n = ;

    fscanf(f, "%d", &n);

    int *money = malloc(sizeof(int) * n);

    if (money == NULL)
    {
        perror("Eroare malloc money");
        exit(-1);
    }

    for (int i = 0; i < n; i++)
    {
        fscanf(f, "%d", &money[i]);
    }
*/

int n=3;
int *money = malloc(sizeof(int) * n);
money[0] = 1;
money[1] = 5;
money[2] = 10;

    int sum = 100;
/*    printf("Suma = ");
    scanf("%d", &sum);
*/
    int sol[n];

    back(0, sol, n, sum, money);

/*    if (fclose(f) != 0)
    {
        perror("Eroare inchidere fisier N.TXT");
        exit(-1);
    }
*/
    free(money);

    return 0;
}