#include <stdio.h>

/* Se citeşte de la tastatură dimensiunea n a unei matrici binare (cu elem. 0 sau 1). Să
se formeze toate matricele posibile astfel încât pe fiecare linie respectiv coloană să
fie exact un element nenul.
*/

void print_sol(int *sol, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (sol[i] == j) //cand vreau doar un element sa difere
                printf("1 ");
            else 
                printf("0 ");
            printf("\n");
        }
        printf("\n");
    }
}

int valid(int step, int *sol)
{
    for (int i = 0; i < step; i++)
    {
        if (sol[i] == sol[step])
        {
            return 0;
        }
    }
    return 1;
}

int solution(int step, int n)
{
    return step == n - 1;
}

void back(int step, int n, int *sol)
{
    for (int i = 0; i < n; i++)
    {
        sol[step] = i;
        if (valid(step, sol))
        {
            if (solution(step, n))
            {
                print_sol(sol, n);
            }

            else back(step + 1, n, sol);
        }
        
    }
}

int main()
{
    int n = 0;
    int sol[20];
    printf("n = ");
    scanf("%d", &n);

    back(0, n, sol);
    return 0;
}