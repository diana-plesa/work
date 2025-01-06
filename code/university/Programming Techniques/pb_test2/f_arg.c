#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

/*: Să se scrie o funcție float *allocVec(int n,...) care primește pe prima poziție un număr de elemente
iar apoi n elemente reale. Funcția va aloca dinamic un vector de tip float în care va depune toate elementele.*/

float *allocVec(int n, ...)
{
    va_list ap;
    va_start(ap, n);
    float *array = NULL;
    for (int i = 0; i < n; i++)
    {
        float elem = (float) va_arg(ap, double);
        array = realloc(array, sizeof(float) * (i + 1));

        if (array == NULL)
        {
            perror("Eroare realloc");
            free(array);
            exit(-1);
        }

        array[i] = elem;
    }
    va_end(ap);
    return array;

}

int main(int argc, char **argv)
{
    float *array;
    float *aux = NULL;
    aux = realloc(aux, sizeof(float) * (argc - 1));

    if (aux == NULL)
    {
        perror("Eroare realloc aux");
        exit(-1);
    }

    for (int i = 1; i < argc; i++)
    {
        aux[i] = (atof) (argv[i]);
    }
    
    switch(argc)
    {
        case 2: 
            array = allocVec(argc - 1, aux[1]);
            break;
        case 3:
            array = allocVec(argc - 1, aux[1], aux[2]);
            break;
        case 4:
            array = allocVec(argc - 1, aux[1], aux[2], aux[3]);
            break;
        case 5:
            array = allocVec(argc - 1, aux[1], aux[2], aux[3], aux[4]);
            break;
        default:
            printf("Too many arguments\n");
            return 0;
    }

    for (int i = 0; i < argc - 1; i++)
    {
        printf("%f ", array[i]);
    }
    printf("\n");
    free(array);

    return 0;
}