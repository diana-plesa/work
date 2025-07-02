/*Serviciul de Spionaj are nevoie, in interes national, sa afle informatii din interiorul unei corporatii considerate ca fiind sub 
controlul unei entitati adversare.
Se stie ca aceasta corporatie are un sistem de gestiune a permisiunilor de access in care unele permisiuni pot implica si altele. (ex: 
pentru avea access la resursele dintr-un birou un angajat trebuie sa aiba access si sa deschida usa de la etajul unde se afla biroul 
respectiv, acestea fiindconsiderate doua permisiuni distincte).
Serviciul de Spionaj a reusit sa obtina prin metode specifice un fisier de backup al sistemului de securitate.
De asemenea Serviciul de Spionaj a reusit prin analiza sa deduca ca numarul maxim de permisiuni existente este de 20.
Acest fisier are urmatorul format:
■ Pe prima linie gasiti numarul maxim de permisiuni (directe sau mostenite) pe care le poate avea un anumit angajat inainte ca acesta sa fie 
considerat risc de securitate.
■ Pe urmatoarea linie gasiti numarul de permisiuni existente (active).
■ Pe urmatoarele linii (cate permisiuni atatea linii), pe fiecare linie veti gasi un set de numere intregi care realizeaza dependenta unei 
permisiuni de alta..
Astfel pentru fiecare linie (care reprezinta o permisiune) vor existat un numar de coloane (cate una pentru fiecare permisiune), separate 
printr-un spatiu, astfel incat permisiunea de pe coloana j depinde de permisiunea de pe linia i numarul va fi diferit de 0. Daca nu exista 
relatie directa de la permisiunea i la permisiunea j atunci pe linia i, coloana j valoarea va fi 0 (zero).\
Serviciul de Spionaj cere ajutorul studentilor din anul II UPT pentru a rezolva urmatoarele probleme intr-un fisier in care scrieti cod C99, 
pe care sunteti rugati sa il incarcati in timpul alocat: 1. sa determine angajatii care au access la cele mai multe permisiuni, in scopul 
racolarii acestora ca resurse informative.
Pentru aceasta, codul vostru va fi rulat cu fisierul de backup al sistemului de securitate ca prim argument in linia de comanda.
La iesirea standard, veti afisa permisiunea (indicele) care implica accesul ce cele mai multe alte permisiuni.
Lasati in slujba Serviciului de Spionaj sa gaseasca angajatii care au aceasta permisiunie, odata ce permisiunea e cunoscuta.
Pe langa rezultatul digital, pentru atasarea la dosar sunteti rugati:
1.a. sa explicati in detaliu structura de date aleasa pentru a rezolva aceasta problema,
1.b. sa justificati alegerea acestei structuri,
1.c. sa propuneti un exemplu de asemenea structura cu 10 noduri,
1.d. rationamentul pe scurt cum ati ajuns sa gasiti permisiunea cautata.
Nu uitati sa treceti pe acea foaie numele si prenumele pentru a nu exista confuzii in cazul in care solutia propusa va duce la decernarea unei 
medalii persoanei care a rezolvat problema intr-un mod care a dus la indeplinirea misiunii.
2. Serviciul de Spionaj este de asemenea interesat de toti angajatii care sunt considerati risc ridicat de securitate de catre companie.
Prin aceasta sunteti rugati sa gasiti toate permisiunile care, detinute de un angajat ar face din acesta angajat cu risc ridicat de 
securitate in ochii corporatiei.
Dupa rezultatul de la punctul precedent, lasati o linie libera (goala) si afisati in ordine crescatoare indicii permisiunilor care se 
incadreaza in acest caz, separati prin spatiu. Dupa ultimul indice poate sa mai fie un spatiu.
Pentru atasarea la dosarul de colaborare sunteti rugati sa treceti pe hartie logica dupa care ati rezolvat aceasta problema. Sunteti 
rugati sa fiti succinti.
3. Un alt interes general al Serviciului de Spionaj este gasirea de eventuale vulnerabilitati electronice. In acest sens, sunteti rugati 
sa veniti cu o parere, pe foaie, in care sa descrieti in linii mari cum ati detecta bucle de permisiuni care ar putea fi exploatate ca 
riscuri de securitate. Serviciul de Spionaj va multumeste pentru efortul depus.*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_G 20

int threshold;
int nb_p; //number of permissions/nodes
int graph[MAX_G][MAX_G];

void read_file(char filename[])
{
    FILE *f = fopen(filename, "r");

    if (f == NULL)
    {
        perror("Error open file");
        exit(-1);
    }

    fscanf(f, "%d", &threshold);
    fscanf(f, "%d", &nb_p);

    for (int i = 0; i < nb_p; i++)
    {
        for (int j = 0; j < nb_p; j++)
        {
            fscanf(f, "%d", &graph[i][j]);
        }
    }

    if (fclose(f) != 0)
    {
        perror("Error close file");
        exit(-1);
    }
}

void init_w(int w[][MAX_G])
{
    for (int i = 0; i < nb_p; i++)
    {
        for (int j = 0; j < nb_p; j++)
        w[i][j] = graph[i][j];
    }
}

void print_g(int gr[][MAX_G])
{
    for (int i = 0; i < nb_p; i++)
    {
        for (int j = 0; j < nb_p; j++)
        {
            printf("%d ", gr[i][j]);
        }
        printf("\n");
    }
}

int find_perm(int w[][MAX_G])
{
    int max_dependecies = 0;
    int index_max = 0;
    for (int i = 0; i < nb_p; i++)
    {
        int dependencies_count = 0;
        for (int j = 0; j < nb_p; j++)
        {
            if (w[i][j] == 1) dependencies_count++;
        }
        if (dependencies_count > max_dependecies) 
        {
            max_dependecies = dependencies_count;
            index_max = i;
        }
    }

    return index_max;
}

void find_employees(int w[][MAX_G])
{
    for (int i = 0; i < nb_p; i++)
    {
        int dependencies_count = 0;

        for (int j = 0; j < nb_p; j++)
        {
            if (w[i][j] == 1) dependencies_count++;
        }

        if (dependencies_count > threshold)
        {
            printf("%d ", i);
        }
    }
}

void warshal()
{
    int w[MAX_G][MAX_G] = { 0 };
    init_w(w);

    for (int k = 0; k < nb_p; k++)
    {
        for (int i = 0; i < nb_p; i++)
        {
            for (int j = 0; j < nb_p; j++)
            {
                if (w[i][j] == 0 && w[k][j] == 1 && w[i][k] == 1) w[i][j] = 1;
            }
        }
    }
    
    //print_g(w);
    printf("%d\n", find_perm(w)); //exercise 1
    find_employees(w); //exercise 2
}



int main(int argc, char **argv)
{
    read_file(argv[1]);
    warshal();
    return 0;
}