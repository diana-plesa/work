/*Un sistem de diagnostic medical ajuta medicii sa ia decizii de tratament mai repede si mai precis printr-o serie de 
intrebari puse pacientului la care acesta raspunde cu DA sau NU. Un astfel de sistem se numeste Sistem Expert.
Fiecare intrebare duce fie la o alta intrebare fie la un diagnostic/recomandare de tratament care incheie sesiune
de consultatie.
Acest Sistem Expert va este pus la dispozitie intr-un fisier text.
Acest fisier text are urmatoarea structura:
■ Pe prima linie este numarul maxim de intrebari si diagnostice pe care sistemul le cunoaste.
■ Pe urmatoarea linie, separate prin spatiu, incepand cu prima intrebare va fi un numar care precizeaza de care 
intrebare depinde intrebarea cu indicele i. Indicele intrebarilor pornesc de la 1. Prima intrebare va depinde de 
intrebarea virtuala 0 (zero) adica prima intrebare este punctul de intrare in sistem, si intrebarea care va fi 
adresata la inceput tuturor pacientilor atunci cand se prezinta la consultatie.
Sunteti rugati sa proiectati un asemenea sistem care sa rezolve urmatoarele probleme:
1. Sa ghideze automat utilizatorii prin procesul decizional cu intrebari de tip da/nu.
Pe foaie:
Daca nu se ajunge la un diagnostic / tratament, sistemul trebuie sa informeze medicul despre numarul maxim de intrebari 
care mai sunt necesare pentru a fii siguri ca sesiunea de consultatie poate fi incheiata.
Intr-un al doilea fisier, fisierul pacient, se vor gasi pe o singura linie, separat prin spatiu, 
fie numarul O fie numarul 1.
O reprezinta ca pacientul a raspuns negativ la o anumita intrebare, iar 1 reprezinta ca pacientul a raspuns pozitiv 
la acea intrebare.
Considerand ca raspunsurile pacientilor sunt de la inceputul sesiunii de consultatii (nu s-a pierdut nimic),
Scrieti un cod C99, care are in linia de comanda 2 agumente, primul fiind fisierul Sistemului Expert iar al 
doilea argument fiind numele fisierului unui pacient si la iesirea standard afiseaza numarul maxim de intrebari 
care mai pot fi puse acelui pacient pana la ajungerea cu siguranta la un diagnostic/tratament exact.
Exemplificati un asemenea sistem, explicati si justificati structura de date aleasa.
Explicati pe scurt functionarea algoritmului scris in fisierul de cod C99.
2. Afisati la iesirea standard numarul maxim posibil de intrebari care poate fi pus unui pacient oarecare pana cand 
acel pacient primeste un diagnostic / tratament. Dupa ce afisati rezultatul de la pct 1, lasati o linie libera si 
afisati rezultatul de la aceasta cerinta.
Pe foaie explicati modul de rationament.
Atentie! codul vostru va fi rulat o singura data, si va trebui sa raspunda la cele 2 cerinte.*/

#include <stdio.h>
#include <stdlib.h>

#define Q_MAX 25

typedef struct node
{
    int parent; //index of parent
    int yes; //index child left
    int no; //index child right
} QUESTION;

typedef struct tree
{
    int nb_q; //total number of questions
    QUESTION questions[Q_MAX];
} SYS;

SYS sys; //tree

void init_tree()
{
    for (int i = 0; i < Q_MAX; i++)
    {
        sys.questions[i].parent = 0;
        sys.questions[i].no = 0;
        sys.questions[i].yes = 0;
    }
}

void read_file(char filename[])
{
    FILE *f = fopen(filename, "r");

    if (f == NULL)
    {
        perror("Error open file");
        exit(-1);
    }

    fscanf(f, "%d", &sys.nb_q);

    int i = 1;

    while (fscanf(f, "%d", &sys.questions[i].parent) != EOF)
    {
        i++;
    } //parse first file to add values to tree

    if (fclose(f) != 0)
    {
        perror("Error close file");
        exit(-1);
    }
}

void create_children() //fill tree with appropriate yes/no children after reading parents from files
{
    for (int i = 1; i <= sys.nb_q; i++)
    {
        if (sys.questions[i].parent != 0)
        {
            if (sys.questions[sys.questions[i].parent].yes == 0)
                sys.questions[sys.questions[i].parent].yes = i;
            else if (sys.questions[sys.questions[i].parent].no == 0)
                sys.questions[sys.questions[i].parent].no = i;
        }
    }
}

int max_depth(int index)
{
    if (sys.questions[index].no == 0 && sys.questions[index].yes == 0) return 0; //if leaf/diagnostic, end of path

    int right_depth = max_depth(sys.questions[index].yes);
    int left_depth = max_depth(sys.questions[index].no);

    if (right_depth > left_depth) return 1 + max_depth(sys.questions[index].yes);
    else return 1 + max_depth(sys.questions[index].no);

}

void calc_patient(char filename[])
{
    FILE *f = fopen(filename, "r");

    if (f == NULL)
    {
        perror("Error open file");
        exit(-1);
    }

    int current = 1, ans = 0; //current = index through tree based on patient's answers

    while (fscanf(f, "%d", &ans) != EOF) //parse patient answers
    {
        if (ans == 1)
        {
            current = sys.questions[current].yes;
        }
        else 
        {
            current = sys.questions[current].no;
        }
    }


    printf("%d\n", max_depth(current)); //longest path from current position

    if (fclose(f) != 0)
    {
        perror("Error close file");
        exit(-1);
    }
}

void print_tree()
{
    for (int i = 0; i <= sys.nb_q; i++)
    {
        printf("Node = %d, Parent = %d, Yes = %d, No = %d\n",
        i, sys.questions[i].parent, sys.questions[i].yes, sys.questions[i].no);
    }
}

int main(int argc, char **argv)
{
    init_tree();
    read_file(argv[1]);
    create_children();
    calc_patient(argv[2]);
    printf("%d", max_depth(1)); //longest path from root 

    return 0;
}