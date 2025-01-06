#include <stdio.h>
#include <math.h>
#include <stdlib.h>

/*6. Să se scrie un program care calculează valoarea funcțiilor pentru un anumit x citit din fișierul
binar X.IN (fișierul binar se va crea cu ajutorul unei funcții speciale pentru a ne asigura că e creat
corect):
a(x)=b(x)+c(x);
b(x)=d(x)*e(x);
c(x)=f(x)/g(x);
d(x)=sin(x)+2^x;
e(x)=3^x;
f(x)=x;
g(x)=1+2x+3x^2+4x^3;
Operațiile cu funcții se vor implementa cu pointeri la funcții. În funcțiile a, b și c vor fi primite
ca parametrii funțiile b, c, d, e, f și g.
Rezultatele obținute se vor scrie în fișierul text REZULTATE.TXT.*/

void create_file()
{
    float x;
    printf("x = ");
    scanf("%f", &x);

    FILE *f = fopen("X.IN", "wb");

    if (f == NULL)
    {
        perror("Eroare deschidere fisier binar scriere");
        exit(-1);
    }

    fwrite(&x, sizeof(int), 1, f);

    if (fclose(f) != 0)
    {
        perror("Eroare inchidere fisier binar scriere");
        exit(-1);
    }
}

float read_file()
{
    FILE *f = fopen("X.IN", "rb");

    if (f == NULL)
    {
        perror("Eroare deschidere fisier binar citire");
        exit(-1);
    }

    float x = 0;
    fread(&x, sizeof(int), 1, f);

    if (fclose(f) != 0)
    {
        perror("Eroare inchidere fisier binar citire");
        exit(-1);
    }

    return x;
}

float function_g(float x)
{
    //return x;
    return 1 + 2 * x + 3 * pow(x, 2) + 4 * pow(x, 3);
}

float function_f(float x)
{
    return x / 2;
}

float function_e(float x)
{
    return pow(3, x);
}

float function_d(float x)
{
    return sin(x) + pow(2, x);
}

float function_c(float x, float (*f)(float), float (*g)(float))
{
    return f(x) / g(x);
}

float function_b(float x, float(*d)(float), float(*e)(float))
{
    return d(x) * e(x);
}

float function_a(float x, float (*b)(float x, float (*)(float), float (*)(float)), float (*c)(float, float (*)(float), float (*)(float)))
{
    return b(x, function_d, function_e) + c(x, function_f, function_g);
}

void write_file(float val)
{
    FILE *f = fopen("REZULTATE.TXT", "w");

    if (f == NULL)
    {
        perror("Eroare deschidere fisier text");
        exit(-1);
    }

    fprintf(f, "%f", val);

    if (fclose(f) != 0)
    {
        perror("Eroare inchidere fisier text");
        exit(-1);
    }
}


int main()
{
    create_file();
    float x = read_file();

    float(*a)(float, float(*)(float, float(*)(float), float(*)(float)), float(*)(float, float(*)(float), float(*)(float)));
    float (*b)(float, float(*)(float), float(*)(float));
    float (*c)(float, float(*)(float), float(*)(float));

    c = &function_c;
    b = &function_b;
    a = &function_a;

    float val = a(x, b, c);

    printf("a(%f) = %f\n", x, val);

    write_file(val);
    


    return 0;
}