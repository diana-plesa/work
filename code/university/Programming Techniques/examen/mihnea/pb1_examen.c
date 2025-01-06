#include <stdio.h>
#include <stdlib.h>

typedef struct elem{
    int info;
    struct elem* urm;
}elem;

elem* creareNod(elem* lista, int n){
    elem* nod = (elem*) malloc(sizeof(elem));
    if(nod == NULL){
        printf("Memorie insuficienta!");
        exit(-1);
    }

    nod -> info = n;
    nod -> urm = NULL;

    if(lista == NULL)
        return nod;

    elem* p = lista;
    while(p -> urm != NULL)
        p = p -> urm;
    
    p -> urm = nod;
    nod -> urm = NULL;

    return lista;
}

void eliberareMemorie(elem* lista){
    // elem* p;
    // while(p != NULL){
    //     p = lista;
    //     lista = lista -> urm;
    //     free(p);
    // }

    elem* cursor;

    cursor = lista;

    while (cursor != NULL)
    {
        elem *aux;
        aux = cursor -> urm;
        free(cursor);
        cursor = aux;
    }
}

elem* sumaElementelor(elem* lista){
    elem* p = NULL;
    elem* q = lista;

    while(q -> urm != NULL){
        int s = q -> info + q -> urm -> info;
        //printf("aici1\n");
        p = creareNod(q, s);
        //printf("aici2\n");
        q = q -> urm;
    }
    return p; //returnam noul cap
}

void afisare(elem* lista){
    while(lista != NULL){
        printf("%d ", lista -> info);
        lista = lista -> urm;
    }
}

int main(int argc, char* argv[]){
    if(argc != 2){
        printf("Eroare!");
        exit(-1);
    }

    FILE* f = fopen(argv[1], "r");
    if(f == NULL){
        printf("Eroare la deschiderea fisierului!");
        exit(-1);
    }

    int n;
    fscanf(f, "%d", &n);

    elem* lista = NULL;
    for(int i = 0; i < n; i++){
        int value;
        fscanf(f, "%d", &value);
        lista = creareNod(lista, value);
    }
    fclose(f);



    int i = 1;
    while(lista != NULL && lista -> urm != NULL){
        
        printf("Iteratia %d: ", i);
        afisare(lista);
        
        elem* p = sumaElementelor(lista);
        printf("aici\n");
        //eliberareMemorie(lista);
        lista = p;
        i++;
    }

    if(lista != NULL){
        printf("Iteratia %d: ", i);
        afisare(lista);
        eliberareMemorie(lista);
    }

    return 0;
}