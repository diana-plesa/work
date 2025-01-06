#include <stdio.h>

void print(int *sol, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d ", sol[i]);
    }
    printf("\n");
}

int solution(int step, int *sol, int n)
{
    return step == n - 1;
}

int valid(int step, int *sol)
{
    for (int i = 0 ; i < step; i++)
    {
        if (sol[i] == sol[step])
            return 0;
    }
    return 1;
}

void back(int step, int *sol, int n)
{
    for (int i = 1; i <= n; i++)
    {
        sol[step] = i;

        if (valid(step, sol))
        {
            if (solution(step, sol, n))
                print(sol, n);
            else 
                back(step + 1, sol, n);
        }
    }
}

int main()
{
    int n = 5;
    int sol[10];
    back(0, sol, 5);
}