#include <stdio.h>
#include <stdlib.h>

/*Să se scrie o funcție care primește o listă și returnează lista respectivă cu elementele
inversate. Funcția va acționa doar asupra listei originare, fără a folosi vectori sau alocare de noi
elemente.*/

typedef struct list
{
    int info;
    struct list *next;
}node;

node *new_node(int val)
{
    node *new = malloc(sizeof(node));

    if (new == NULL)
    {
        printf("error malloc");
        exit(-1);
    }

    new -> info = val;
    new -> next = NULL;

    return new;
}

node *add_to_end(node *start, node *new)
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

void print_list(node *start)
{
    for (node *cursor = start; cursor != NULL; cursor = cursor -> next)
    {
        printf("%d ", cursor -> info);
    }
    printf("\n");
}

void free_list(node *start)
{
    node *cursor = start;
    while (cursor != NULL)
    {
        node* node_next = cursor -> next;
        free(cursor);
        cursor = node_next;
    }
}

node *invert_list(node *start)
{
    node *cursor = start -> next -> next, *a = start, *b = start -> next;
    while (cursor != NULL)
    {
        b -> next = a;
        a = b;
        b = cursor;
        cursor = cursor -> next;
    }

    b -> next = a;
    start -> next = NULL;
    start = b;

    return start;
}

int main()
{
    node *new, *start = NULL;

    new = new_node(1);
    start = add_to_end(start, new);

    new = new_node(2);
    start = add_to_end(start, new);

    new = new_node(3);
    start = add_to_end(start, new);

    new = new_node(4);
    start = add_to_end(start, new);

    print_list(start);

    start = invert_list(start);
    print_list(start);

    //caz de 2 elemente!

    free_list(start);

    return 0;
}