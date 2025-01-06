#include <stdio.h>
#include <stdlib.h>

/* Se dă un vector x cu n elemente numere naturale, ordonate crescător, și un
vector y cu m elemente, de asemenea numere naturale. Verificați pentru
fiecare element al vectorului y dacă apare în x. Se va folosi tehnica Divide et
Impera*/

int seek_el(int *y, int start_y, int length_y, int *x, int n)
{
    if (length_y > start_y)
    {
        return 1;
    }

    if (length_y == start_y)
    {
        for (int i = 0; i < n; i++)
        {
            if (y[start_y] == x[i])
            {
                return 1;
            }
        }
        return 0;
    }

    int middle_index = (start_y + length_y) / 2;
    int left = seek_el(y, start_y, middle_index, x, n);
    int right = seek_el(y, middle_index + 1, length_y, x, n);

    if (left == 1 && right == 1)
    {
        return 1;
    }
    else 
    {
        return 0;
    }

}

int main()
{
    int n = 0, m = 0;
    printf("n = ");
    scanf("%d", &n);
    printf("m = ");
    scanf("%d", &m);

    int *x = malloc(sizeof(int) * n);

    if (x == NULL)
    {
        perror("Eroare malloc x\n");
        exit(-1);
    }

    int *y = malloc(sizeof(int) * m);

    if (y == NULL)
    {
        perror("Eroare malloc x\n");
        exit(-1);
    }

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &x[i]);
    }

    for (int i = 0; i < m; i++)
    {
        scanf("%d", &y[i]);
    }

    int val = seek_el(y, 0, m - 1, x, n - 1);

    if (val == 1)
    {
        printf("Toate elementele din y apar in x\n");
    }
    else 
    {
        printf("Nu toate elementele din y apar in x\n");
    }

    return 0;
}