#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*In doua fisiere text MultimeA.TXT si MultimeB.TXT se gasesc 2 multimi A si respectiv B
cu elemente numere naturale.
a) Sa se creeze cate o lista liniara simplu inlantuita pentru memorarea elementelor din fiecare
dintre cele 2 multimi.
b) Sa se scrie o functie care primeste parametrii adresele primului nod ale celor 2 multimi si
creaza si returneaza o noua lista liniara simplu inlantuita care memoreaza reuniunea celor 2
multimi.
c) Sa se scrie o functie care primeste parametrii adresele primului nod ale celor 2 multimi si
creaza si returneaza o noua lista liniara simplu inlantuita care se memoreze intersectia celor 2
multimi.
d) Sa se modifice informatiile din cele 2 fisiere din care s-a citit astfel incat fiecare fisier, pe
langa multimea initiala, sa contina, pe urmatoarele 2 randuri multimea reuniune, respectiv
multimea intersectie.*/

typedef struct list
{
    int info;
    struct list *next;
}node;

node* new_node(int val)
{
    node *new;
    new = malloc(sizeof(node));

    if (new == NULL)
    {
        perror("eroare malloc nod nou");
        exit(-1);
    }

    new -> info = val;
    new -> next = NULL;

    return new;
}

node* add_to_end(node *start, node *new)
{
    if (start == NULL)
    {
        return new;
    }

    node *cursor;

    for (cursor = start; cursor -> next != NULL; cursor = cursor -> next);

    cursor -> next = new;
    return start;
}

node* new_list(node *start, char *file_name)
{
    FILE *f = fopen(file_name, "r");

    if (f == NULL)
    {
        perror("Eroare deschidere fisier");
        exit(-1);
    }
    int val;
    node *new;

    while (fscanf(f, "%d", &val) != EOF)
    {
        //printf("%d ", val);
        new = new_node(val);
        start = add_to_end(start, new);
    }

    if (fclose(f) != 0)
    {
        perror("Eroare inchidere fisier");
        exit(-1);
    }

    return start;

}

void print_list(node *start)
{
    if (start == NULL)
    {
        printf("Empty list\n");
        return;
    }

    node *cursor;

    for (cursor = start; cursor != NULL; cursor = cursor -> next)
    {
        printf("%d ", cursor -> info);
    }
    printf("\n");
    return;
}

node* make_intersection(node *start1, node *start2)
{
    node *new, *start = NULL, *cursor1, *cursor2;

    for (cursor1 = start1; cursor1 != NULL; cursor1 = cursor1 -> next)
    {
        for (cursor2 = start2; cursor2 != NULL; cursor2 = cursor2 -> next)
        {
            if (cursor1 -> info == cursor2 -> info)
            {
                new = new_node(cursor1 -> info);
                start = add_to_end(start, new);
            }
        }
    }

    return start;
}

int is_found(node *start, int val)
{
    node *cursor;

    for (cursor = start; cursor != NULL; cursor = cursor -> next)
    {
        if (cursor -> info == val)
            return 1;
    }

    return 0;
}

node *make_reunion(node *start1, node *start2)
{
    node *start = NULL, *new, *cursor1, *cursor2;

    for (cursor1 = start1; cursor1 != NULL; cursor1 = cursor1 -> next)
    {
        new = new_node(cursor1 -> info);
        start = add_to_end(start, new);
    }
        for (cursor2 = start2; cursor2 != NULL; cursor2 = cursor2 -> next)
        {
            if (is_found(start, cursor2 -> info) == 0)
            {
                new = new_node(cursor2 -> info);
                start = add_to_end(start, new);
            }
        }

    
    return start;
}

void modify_file(char *file_name, node *start3, node *start4)
{
    FILE *f = fopen(file_name, "a");

    if (f == NULL)
    {
        perror("Eroare scriere deschidere fisier");
        exit(-1);
    }

    node *cursor;

    for (cursor = start3; cursor != NULL; cursor = cursor -> next)
    {
        fprintf(f, "%d ", cursor -> info);
    }
    fprintf(f, "\n");

    for (cursor = start4; cursor != NULL; cursor = cursor -> next)
    {
        fprintf(f, "%d ", cursor -> info);
    }
    fprintf(f, "\n");

    if (fclose(f) != 0)
    {
        perror("Eroare scriere inchidere fisier");
        exit(-1);
    }
}

void free_list(node *start)
{
    node *cursor = start, *node_next;

    while (cursor != NULL)
    {
        node_next = cursor -> next;
        free(cursor);
        cursor = node_next;
    }
}

int main()
{
    node *start1 = NULL, *start2 = NULL, *start3 = NULL, *start4 = NULL;

    start1 = new_list(start1, "MultimeA.TXT");
    start2 = new_list(start2, "MultimeB.TXT");

    print_list(start1);
    print_list(start2);

    start3 = make_intersection(start1, start2);
    print_list(start3);

    start4 = make_reunion(start1, start2);
    print_list(start4);

    modify_file("MultimeA.TXT", start3, start4);
    modify_file("MultimeB.TXT", start3, start4);

    free_list(start1);
    free_list(start2);
    free_list(start3);
    free_list(start4);


    return 0;
}