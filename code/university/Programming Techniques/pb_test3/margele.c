#include <stdio.h>
#include <stdlib.h>

/*Se dau mărgele de 5 culori: alb, roşu, verde, albastru, negru. Numărul mărgelelor de
fiecare culoare se consideră nelimitat. Să se afişeze toate colierele de n mărgele
care se pot forma, respectând următoarele condiţii:
- nu poate fi plasată o mărgea verde lângă o mărgea albastră;
- nu pot fi plasate mărgele vecine de aceeaşi culoare;
- numărul mărgelelor roşii nu poate depăşi o treime din numărul total de
mărgele din colier.
*/

void print(int sol[], int v[], int n) 
{
    for (int i = 0; i < n; i++)
        printf("%d ", v[sol[i]]);

    printf("\n");
}

int valid(int step, int *sol, int *v, int n)
{
    int reds = 0;
    for (int i = 0; i < step; i++)
    {
        if (v[sol[i]] == 1) reds++;

        if ((v[sol[i]] == 3 && v[sol[i + 1]] == 4) || (v[sol[i]] == 4 && v[sol[i + 1]] == 3))
            return 0;
        
        if (v[sol[i]] == v[sol[i + 1]])
            return 0;
        
        if (reds > n / 3)
            return 0;
    }
    return 1;
}

int solution(int step, int n)
{
    return step == n - 1;
}

void back(int step, int *sol, int *v, int n)
{
    for (int i = 0; i < n; i++)
    {
        sol[step] = i;

        if (valid(step, sol, v, n))
        {
            if (solution(step, n))
            {
                print(sol, v, n);
            }
            else 
            {
                back(step + 1, sol, v, n);
            }
        }
    }
}

int main()
{
    int n = 0;
    printf("Lungime colier = ");
    scanf("%d", &n);
    int *sol = malloc(sizeof(int) * n);
    int *beads = malloc(sizeof(int) * n);

    if (sol == NULL)
    {
        perror("Eroare malloc sol");
        exit(-1);
    }

    if (beads == NULL)
    {
        perror("Eroare malloc vector");
        exit(-1);
    }

    printf("1 = Alb\n");
    printf("2 = Rosu\n");
    printf("3 = Verde\n");
    printf("4 = Albastru\n");
    printf("5 = Negru\n");

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &beads[i]);
    }

    back(0, sol, beads, n);
    free(sol);
    free(beads);

    return 0;
}