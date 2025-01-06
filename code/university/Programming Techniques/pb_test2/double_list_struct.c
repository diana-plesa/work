#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Să se imlementeze o listă dublu înlănțuită care gestionează un parc de automobile. Informaţiile
relative la un automobil sunt: codul mașinii (număr între 1 si 9000), numărul de locuri (între 1 și 9), puterea (în cai
putere între 1 și 500), marca, culoarea, anul fabricaţiei maşinii (între 1800 și 2017). Parcul conține n automobile,
datele sunt citite de la tastatură. Să se scrie următoarele funcții de gestiune a mașinilor:
a) Introducerea unui automobil nou în listă la începutul listei;
b) Ștergerea unui anumit automobil din listă, al cărui cod e citit de la tastatură;
c) Afișarea întregii liste pe ecran;
d) Afișarea pe ecran doar a automobilelor cu un anumit număr de locuri, citit de la tastatură;
e) Ordonarea listei în funcție de anul fabricației.
Să se definească structura pentru o mașină cu ajutorul structurilor cu câmpuri pe biți astfel încât spațiul ocupat să
fie minim*/

typedef struct 
{
    unsigned int code:14;
    unsigned int seats:4;
    unsigned int pow:9;
    unsigned int year:11;
    char brand[10];
    char color[10];
}car;

typedef struct list 
{
    car info;
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
    int code, seats, pow, year;
    car val;
    node *new = malloc(sizeof(node));
    printf("Code: ");
    scanf("%d", &code);
    val.code = code;
    printf("Number seats: ");
    scanf("%d", &seats);
    val.seats = seats;
    printf("Horse power: ");
    scanf("%d", &pow);
    val.pow = pow;   
    printf("Year of fabrication: ");
    scanf("%d", &year);
    val.year = year;
    printf("Brand: ");
    scanf("%9s", val.brand);
    printf("Color: ");
    scanf("%9s", val.color);
    getchar();

    memcpy(&(new -> info), &val, sizeof(val));
    new -> next = NULL;
    new -> prev = NULL;
    return new;
}

indicator add_to_head(node *new, indicator i)
{
    if (i.start == NULL)
    {
        i.end = new;
    }
    else 
    {
        i.start -> prev = new;
        new -> next = i.start;
    }
    
    i.start = new;
       
    return i;
}

void print_car(car val)
{
    printf("Code: %u\n", val.code);
    printf("Number of seats: %u\n", val.seats);
    printf("Horse power: %u\n", val.pow);
    printf("Year: %u\n", val.year);
    printf("Brand: %s\n", val.brand);
    printf("Color: %s\n", val.color);
    printf("\n");
}

void print_list(indicator i)
{
    if (i.start == NULL) 
    {
        printf("Empty list\n");
        return;
    }

    node *cursor;
    for (cursor = i.start; cursor != NULL; cursor = cursor -> next)
    {  
        print_car(cursor -> info);
        // if (cursor -> prev) printf("PREVIOUS: %s\n", (cursor -> prev -> info).brand);
        // else printf("PREVIOUS: NULL\n");

        // if (cursor -> next) printf("NEXT: %s\n", (cursor -> next -> info).brand);
        // else printf("NEXT: NULL\n");
    }
}

indicator delete_item(indicator i)
{
    if (i.start == NULL)
    {
        printf("Empty list\n");
        return i;
    }

    int code = 0;
    node *cursor = i.start, *aux = i.start;
    printf("Type code: ");
    scanf("%d", &code);

    while (cursor -> next != NULL)
    {
        if ((cursor -> info).code == code)
        {
            aux = cursor;
            if (cursor == i.start)
            {
                i.start = cursor -> next;
                i.start -> prev = NULL;
                free(aux);
                return i;
            }

            if (cursor == i.end)
            {
                i.end = cursor -> prev;
                i.end -> next = NULL;
                free(cursor);
                return i;
            }

            cursor -> prev -> next = cursor -> next;
            cursor -> next -> prev = cursor -> prev;
            cursor = cursor -> next;
            free(aux);

            return i;
        }
        else 
        {
            cursor = cursor -> next;
            cursor -> prev = cursor -> prev -> next;
        }
    }

    printf("Given code is not in list\n");

    return i;

}

void print_items(indicator i)
{
    int val = 0;
    printf("Type seat number: ");
    scanf("%d", &val);
    for (node *cursor = i.start; cursor != NULL; cursor = cursor -> next)
    {
        if ((cursor -> info).seats == val) 
        {
            print_car(cursor -> info);
            return;
        }
    }

    printf("Given seat number does not exist\n");
}

void switch_nodes(node *a, node *b)
{
    car aux;
    memcpy(&aux, &(a -> info), sizeof(car));
    memcpy(&(a -> info), &(b -> info), sizeof(car));
    memcpy(&(b -> info), &aux, sizeof(car));

}

indicator sort_list(indicator i)
{
    node *cursor1 = i.start;
    node *cursor2 = NULL;

    for (cursor1 = i.start; cursor1 != NULL; cursor1 = cursor1 -> next)
    {
        for (cursor2 = cursor1 -> next; cursor2 != NULL; cursor2 = cursor2 -> next)
        {
            if ((cursor1 -> info).year > (cursor2 -> info).year)
            {
                switch_nodes(cursor1, cursor2);
            }
        }
    }

    return i;

}

int main()
{
    char opt = 0;
    node *new = NULL;
    indicator i;

    i.start = NULL, i.end = NULL;


    for(;;)
    {
        printf("a. Add to list\n");
        printf("b. Delete item\n");
        printf("c. Print list\n");
        printf("d. Print cars with given seat number\n");
        printf("e. Sort list by year\n");
        printf("f. End\n");
        printf("Choose option: ");
        opt = getchar(); 

        switch(opt)
        {
            case 'a':
                new = new_node();
                i = add_to_head(new, i);
                break;

            case 'b':
                i = delete_item(i);
                getchar();
                break;

            case 'c':
                print_list(i);
                getchar();
                break;

            case 'd':
                print_items(i);
                getchar();
                break;

            case 'e':
                i = sort_list(i);
                getchar();
                break;

            // case 'f':
            //     break;

        }
    }
    return 0;
}