#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Un program bibliotecar tine evidenta cartilor imprumutate de diferiti cititori.Informatiile
pentru fiecare imprumut includ (primele patru campuri sunt alfanumerice) : titlu carte,
autor carte, nume cititor, adresa cititor, termen(numar de zile pana la returnare).
Sa se implementeze operatorii :
• vidare() - se initializeaza evidenta, nici o carte imprumutata;
• imprumut_nou(titlu_carte, autor_carte, nume_cititor, adresa_cititor,
termen_returnare) adauga un imprumut nou, daca cititorul cu numele dat nu mai are
carti imprumutate; daca are, atunci imprumutul nu va fi efectuat;
• actualizare() - pentru fiecare carte imprumutata, se decrementeaza termenul de
returnare cu o unitate; dupa decrementare se afiseaza cititorii care nu au returnat
cartile la timp in ordine descrescatoare a intarzierilor;
• returnare(nume_cititor) - cartea detinuta de cititorul cu numele precizat este
returnata, ea trebuind stearsa din evidenta;
• afisare() - se afiseaza evidenta*/

typedef struct 
{
    char title[10];
    char author[20];
    char reader[20];
    char address[30];
    int deadline;
}BOOK;

typedef struct list
{
    BOOK info;
    struct list *next;
}node;

node *new_node()
{
    node *new = malloc(sizeof(node));
    if (new == NULL)
    {
        perror("Eroare malloc");
        exit(-1);
    }

    printf("Titlu: ");
    scanf("%9s", (new -> info).title);
    printf("Nume autor: ");
    scanf("%19s", (new -> info).author);
    printf("Nume cititor: ");
    scanf("%19s", (new -> info).reader);
    printf("Adresa: ");
    scanf("%29s", (new -> info).address);
    printf("Deadline: ");
    scanf("%d", &(new -> info).deadline);

    new -> next = NULL;
    return new;

}

node *add_to_end(node *new, node *start)
{
    if (start == NULL)
        return new;
    
    node *cursor;
    for(cursor = start; cursor -> next != NULL; cursor = cursor -> next);

    cursor -> next = new;
    new -> next = NULL;

    return start;
}

void print_info(BOOK val)
{
    printf("Titlu: %s\n", val.title);
    printf("Nume autor: %s\n", val.author);
    printf("Nume cititor: %s\n", val.reader);
    printf("Adresa: %s\n", val.address);
    printf("Deadline: %d\n", val.deadline);
    printf("\n");   
}

void print_list(node *start)
{
    if (start == NULL)
    {
        printf("Lista goala\n");
        return;
    }

    node *cursor;
    for (cursor = start; cursor != NULL; cursor = cursor -> next)
    {
        print_info(cursor -> info);
    }
}

void free_list(node *start)
{
    if (start == NULL)
        return;
    
    node *cursor = start, *aux;
    
    while (cursor != NULL)
    {
        aux = cursor;
        cursor = cursor -> next;
        free(aux);
    }
}

node *decrease_deadline(node *start)
{
    if (start == NULL)
    {
        printf("Lista goala\n");
        return start;
    }

    node *cursor;
    for(cursor = start; cursor != NULL; cursor = cursor -> next)
    {
        (cursor -> info).deadline --;
    }
    return start;
}

void switch_nodes(node *a, node *b)
{
    BOOK aux;
    memcpy(&aux, &(a -> info), sizeof(BOOK));
    memcpy(&(a -> info), &(b -> info), sizeof(BOOK));
    memcpy(&(b -> info), &aux, sizeof(BOOK));
}

node *sort_list(node *start)
{
    if (start == NULL) 
    {
        printf("Lista goala\n");
        return start;
    }

    if (start -> next == NULL)
    {
        return start;
    }

    node *cursor1, *cursor2;

    for (cursor1 = start; cursor1 != NULL; cursor1 = cursor1 -> next)
    {
        for (cursor2 = cursor1 -> next; cursor2 != NULL; cursor2 = cursor2 -> next)
        {
            if ((cursor1 -> info).deadline > (cursor2 -> info).deadline)
            {
                switch_nodes(cursor1, cursor2);
            }
        }
    }

    return start;
}

void print_sorted_list(node *start)
{
    if (start == NULL)
    {
        printf("Lista goala\n");
        return;
    }

    node *cursor;

    for (cursor = start; cursor != NULL && (cursor -> info).deadline < 0; cursor = cursor -> next)
        print_info(cursor -> info);

}

char add_str(BOOK info)
{
    
}

int main()
{
    char opt;
    FILE *f = fopen("inventar.txt", "w");

    if (f == NULL)
    {
        perror("Eroare deschidere fisier\n");
        exit(-1);
    }

    node *start = NULL, *new = NULL;

    for(;;)
    {
        printf("1. vidare\n");
        printf("2. Imprumut nou\n");
        printf("3. Actualizare\n");
        printf("4. Returnare\n");
        printf("5. Afisare\n");
        printf("Alege optiunea: ");
        opt = getchar();

        switch(opt)
        {
            case '1':
                free_list(start);
                getchar();
                break;
            case '2':
                new = new_node();
                add_str(new -> info);
                add_to_end(new, start);
                getchar();
                break;
            case '3':
                start = decrease_deadline(start);
                start = sort_list(start);
                print_sorted_list(start);
                getchar();
                break;
            case '5':
                print_list(start);
                getchar();
                break;
        }
    }
}