#include <stdio.h>
#include <stdlib.h>

/*Să se memoreze următoarele informații despre n persoane: numele (șir de caractere de maxim
20 de caractere), prenumele (șir de caractere de maxim 20 de caractere), data nașterii, sexul și
starea civilă (căsătorit, necăsătorit, divorțat, văduv). Dacă este căsătorit se va reține numărul de
copii (număr natural, maxim 20), dacă este necăsătorit se va reține înălțimea (număr real), dacă
este divorțat se va reține de cât timp este divorțat (număr natural, maxim 80), iar dacă este văduv
se va reține inițiala numelui fostului partener (literă).
Să se folosească structuri, uniuni, enumerări și structuri cu câmpuri pe biți astfel încât structura
să ocupe spațiul de memorie optim.
Să se citească n persoane din fișierul text DATE.TXT și să se afișeze pe ecran.
Să se scrie o funcție care calculează vârsta fiecărei persoane în ani împliniți și o afișează pe
ecran.
*/

typedef union 
{
    unsigned int children:5;
    unsigned int divorced_time:7;
    float height;
    char spouse_initial;
}STATE;


typedef struct 
{
    unsigned int birth_year:11;
    unsigned int sex:1;
    unsigned int civil_state:2;
    STATE state_data;
    char last_name[20];
    char first_name[20];
}PERSON;

void read_person(PERSON *x, FILE *f)
{
    fscanf(f, "%20s %20s", x->first_name, x->last_name);
    unsigned int b_year;
    fscanf(f, "%u", &b_year);
    x->birth_year = b_year;
    unsigned int aux_sex;
    fscanf(f, "%u", &aux_sex);
    x->sex = aux_sex;
    unsigned int aux_state;
    fscanf(f, "%u", &aux_state);
    x->civil_state = aux_state;
    
    if (x->civil_state == 0)
    {
        unsigned int aux_children;
        fscanf(f, "%u", &aux_children);
        x->state_data.children = aux_children;
    }

    if (x->civil_state == 1)
    {
        fscanf(f, "%f", &(x->state_data.height));
    }

    if (x->civil_state == 2)
    {
        unsigned int aux_divorced_time;
        fscanf(f, "%u", &aux_divorced_time);
        x->state_data.divorced_time = aux_divorced_time;
    }

    if (x->civil_state == 3)
    {
        fscanf(f, "%c", &x->state_data.spouse_initial);
    }
    
}

void print_person(PERSON x)
{
    printf("Full name: %s %s\n", x.last_name, x.first_name);
    printf("Birth year: %u\n", x.birth_year);
    printf("Sex: %u\n", x.sex);
    printf("Civil state: %u\n", x.civil_state);

    if (x.civil_state == 0)
    {
        printf("Number of children: %u\n", x.state_data.children);
    }

    if (x.civil_state == 1)
    {
        printf("Height: %.2f\n", x.state_data.height);
    }

    if (x.civil_state == 2)
    {
        printf("Years divorced: %.u\n", x.state_data.divorced_time);
    }

    if (x.civil_state == 3)
    {
        printf("Spouse initial: %c\n", x.state_data.spouse_initial);
    }
    
    printf("\n");
}

void process_data()
{
    FILE *f = fopen("DATE.TXT", "r");

    if (f == NULL)
    {
        perror("Eroare deschidere fisier");
        exit(-1);
    }

    int n;
    fscanf(f, "%d", &n);

    PERSON persons[n];

    for (int i = 0; i < n; i++)
    {
        read_person(&persons[i], f);
    }

    for (int i = 0; i < n; i++)
    {
        print_person(persons[i]);
    }

    if (fclose(f) != 0)
    {
        perror("Eroare inchidere fisier");
        exit(-1);
    }
}

int main()
{
    process_data();
    return 0;
}