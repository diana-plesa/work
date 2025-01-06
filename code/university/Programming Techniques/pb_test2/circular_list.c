#include <stdio.h>
#include <stdlib.h>

/*Se considera o lista circulara simplu inlantuita. Sa se scrie o functie care determina
numarul de elemente din lista*/

typedef struct list 
{
    int info;
    struct list *next;
    struct list *prev;
}node;

typedef struct 
{
    node *start;
    node *end;
}indicator;

node *new_node()
{
    int val = 0;
    printf("Valoare nod: ");
    scanf("%d", &val);
    node * new = malloc(sizeof(node));

    if (new == NULL)
    {
        perror("Eroare malloc");
        exit(-1);
    }

    new -> info = val;
    new -> next = NULL;
    new -> prev = NULL;
    return new;
}

indicator add_to_end(node *new, indicator i)
{
    if (i.start == NULL)
    {
        i.start = new;
        i.end = new;
        return i;
    }

    node *cursor;

    for (cursor = i.start; cursor != i.end; cursor = cursor -> next);

    cursor -> next = new;
    i.end = cursor -> next;
    i.end -> next = i.start;
    i.end -> prev = cursor;
    i.start -> prev = i.end;
    return i;
}

void print_list(indicator i)
{
    if (i.start == NULL)
    {
        printf("Lista goala\n");
        return;
    }

    if (i.start == i.end)
    {
        printf("%d\n", i.start -> info);
        return;
    }

    node *cursor;

    for (cursor = i.start; cursor -> next != i.start; cursor = cursor -> next)
    {
        printf("%d ", cursor -> info);
    }
    printf("%d\n", cursor -> info);
    // printf("start prev: %d\n", i.start -> prev -> info);
    // printf("end next: %d\n", i.end -> next -> info);
}

void free_list(indicator i)
{
    if (i.start == NULL)
    {
        printf("Lista goala\n");
        return;
    }

    if (i.start == i.end)
    {
        free(i.start);
        return;
    }

    node *cursor, *aux;

    for (cursor = i.start; cursor -> next != i.start; cursor = cursor -> next)
    {
        aux = cursor;
        free(aux);
    }

    free(cursor);
    return;
}

int length(indicator i)
{
    if (i.start == NULL) return 0;
    if (i.start == i.end) return 1;
    node *cursor;
    int length = 1;
    for (cursor = i.start; cursor -> next != i.start; cursor = cursor -> next)
    {
        length++;
    }

    return length;
}

int main()
{
    char opt = 0;
    node *new;
    indicator i;
    i.start = NULL;
    i.end = NULL;

    for (;;)
    {
        printf("a. Adauga element in lista\n");
        printf("b. Printeaza lista\n");
        printf("c. Afla lungimea listei\n");
        printf("d. Final\n");
        printf("Choose option: ");
        opt = getchar();
        
        switch(opt)
        {
            case 'a':
                new = new_node();
                i = add_to_end(new, i);
                getchar();
                break;

            case 'b':
                print_list(i);
                getchar();
                break;
            case 'c':
                printf("%d\n", length(i));
                getchar();
                break;
            case 'd':
                free_list(i);
                return 0;
                break;
        }
    }

    return 0;
}