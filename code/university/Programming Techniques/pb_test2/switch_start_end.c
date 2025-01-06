#include <stdio.h>
#include <stdlib.h>

typedef struct nod{
    int inf;
    struct nod* urm;
}nod;

nod* interschimbare(nod* inceput){
    if(inceput == NULL)
        return inceput;

    if (inceput -> urm == NULL)
        return inceput;
    
    nod* current, *prev;
    current = inceput;
    prev = NULL;
    
    while(current -> urm != NULL){
        prev = current;
        current = current -> urm;
    }
    
    prev -> urm = inceput;
    current -> urm = inceput -> urm;
    inceput -> urm = NULL;    
    inceput = current;
    
    return inceput;
}

void afisare(nod* inceput){
    nod* q;
    q = inceput;
    while(q != NULL){
        printf("%d ", q -> inf);
        q = q -> urm;
    }
}

nod* creare(){
    nod* nou;
    nou = (nod*) malloc(sizeof(nod));
    if(nou == NULL){
        printf("Eroare!\n");
        exit(-1);
    }
    
    int valoare;
    printf("Introduceti valoarea nodului: ");
    scanf("%d", &valoare);
    
    nou -> inf = valoare;
    nou -> urm = NULL;
    return nou;
}

nod* adaugaInceput(nod* inceput, nod* nou){
    if(inceput == NULL){
        inceput = nou;
        return inceput;
    }
    
    nou -> urm = inceput;
    inceput = nou;
    
    return inceput;
}

int main(){
    nod* nou, *inceput = NULL;
    nou = creare();
    inceput = adaugaInceput(inceput, nou);
    
    nou = creare();
    inceput = adaugaInceput(inceput, nou);
    
    nou = creare();
    inceput = adaugaInceput(inceput, nou);
    
    printf("Lista initiala: ");
    afisare(inceput);
    printf("\n");
    
    printf("Lista dupa interschimbare: ");
    inceput = interschimbare(inceput);
    
    afisare(inceput);
    
}