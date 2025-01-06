#include <stdio.h>
#include <stdlib.h>

/* Se considera un număr par n. Generati toate șirurile de paranteze echilibrate de
lungime n.
*/

void print(int sol[], char v[], int n) 
{
    for (int i = 0; i < n; i++)
        printf("%c ", v[sol[i]]);

    printf("\n");
}

int valid(int step, int *sol, char *v, int n)
{
    int balance = 0;

    for (int i = 0; i <= step; i++) {
        if (v[sol[i]] == '(') balance++;
        else balance--;

        if (balance < 0) return 0;
    }

    if (step == n - 1 && balance != 0) return 0;
    return 1;
}

int solution(int step, int n)
{
    return step == n - 1;
}

void back(int step, int *sol, char *v, int n)
{
    for (int i = 0; i < 2; i++)
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
    printf("n = ");
    scanf("%d", &n);
    int sol[100];
    char p[] = {'(', ')'};

    back(0, sol, p, n);

    return 0;
}