#include <stdio.h>
#include <stdlib.h>

/* Să se scrie o funcție care să elimine nodurile care conțin duplicate dintr-o listă care
are valorile ordonate crescător.*/

typedef struct list 
{
    int info;
    struct list *next;
}node;

node* create_node()
{
    int val = 0;
    printf("Type val: ");
    scanf("%d", &val);

    node* new = malloc(sizeof(node));

    if (new == NULL)
    {
        perror("Error malloc");
        exit(-1);
    }

    new -> info = val;
    new -> next = NULL;

    return new;
}

node* add_to_list(node *new, node *start) //add to end
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
    node *cursor;

    for (cursor = start; cursor != NULL; cursor = cursor -> next)
    {
        printf("%d ", cursor -> info);
    }
    printf("\n");
}

node* delete_duplicates(node *start)
{
    if (start == NULL || start -> next == NULL)
        return start;

    node *cursor, *prev;
    cursor = start -> next;
    prev = start;


    while (cursor != NULL)
    {
        if (prev -> info == cursor -> info)
        {
            node *aux = cursor;
            prev -> next = cursor -> next;
            cursor = cursor -> next;
            free(aux);
        }
        else
        {
            cursor = cursor -> next;
            prev = prev -> next;
        }

    }

    return start;
}

void free_list(node *start)
{
    node *cursor = start, *aux;

    while (cursor != NULL)
    {
        aux = cursor;
        cursor = cursor -> next;
        free(aux);
    }
}

int main()
{
    int opt = 0;
    node *new, *start = NULL;

    for(;;)
    {
        printf("1. Add new node\n");
        printf("2. Print list\n");
        printf("3. Delete nodes that have duplicates\n");
        printf("4. End\n");
        printf("Choose an option: ");
        scanf("%d", &opt);

        switch(opt)
        {
            case 1:
                new = create_node();
                start = add_to_list(new, start);
                break;
            case 2:
                print_list(start);
                break;
            case 3:
                start = delete_duplicates(start);
                break;
            case 4:
                free_list(start);
                return 0;
                break;
        }
        
    }
    return 0;
}