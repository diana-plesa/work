#include <stdio.h>
#include <stdlib.h>

/*Folosind metoda Divide et Impera, scrieți o funcție recursivă care primeste ca parametri un vector a de numere 
naturale și două numere întregi st și dr, returnează 1 dacă  în secvența a[st], a[st+1], ..., a[dr] numerele 
impare alternează cu cele pare, sau returnează 0 dacă există cel puțin două numere alăturate de aceeași paritate.*/

int is_alternating(int *array, int left, int right)
{

    // if (left > right)
    // {
    //     return -1;
    // }

    if (left == right)
    {
        return array[left] % 2 == 0 ? 0:1;
    }

    if (left + 1 == right)
    {
        if (array[left] % 2 != array[right] % 2)
            return 1;
        else 
            return 0;

    }

    int middle_index = (left + right) / 2;

    if (is_alternating(array, left, middle_index) == 1 && is_alternating(array, middle_index + 1, right) == 1 
    && array[middle_index] % 2 != array[middle_index + 1] % 2)
        return 1;
    else 
        return 0;

}

int main()
{
    int n = 0;
    printf("n = ");
    scanf("%d", &n);

    int *array = malloc(sizeof(int) * n);

    if (array == NULL)
    {
        perror("Eroare malloc\n");
        exit(-1);
    }

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &array[i]);
    }
    
    int type = 0;
    type = is_alternating(array, 0, n - 1);
    if (type == 0) printf("Not alternating");
    else printf("Alternates");

    free(array);

    return 0;
}