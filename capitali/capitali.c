#define _GNU_SOURCE // avverte che usiamo le estensioni GNU
#include <assert.h> // permette di usare la funzione assert
#include <errno.h> // necessaria per usare errno
#include <stdbool.h> // gestisce tipo bool (per variabili booleane)
#include <stdio.h> // permette di usare scanf printf etc ...
#include <stdlib.h> // conversioni stringa/numero exit() etc ...
#include <string.h> // funzioni di confronto/copia/etc di stringhe

void termina(const char* messaggio);

typedef struct {
    char* nome;
    double latitudine;
    double longitudine;
} AlberoCapitale;
/*Leggere dal file capitali delle capitali con nome, latitudine e longitudine e fare il mergesort per latitudine*/

void libera_capitali(Capitale** c, int size){
    for (int i = 0; i < size; i++)
    {
        free(c[i]->nome);
        free(c[i]);
    }
    free(c);
    
}

// questa funzione legge un file con all'interno una stringa e la carica in un vettore dinamico di caratteri
Capitale** caricaCapitaliDaFile(char* path, int* size)
{ // size va passata per riferimento
    *size = 0;
    int maxSize = 10;

    Capitale** v = malloc(maxSize * sizeof(Capitale*));
    if (v == NULL)
        termina("Memoria insufficiente");
    FILE* f = fopen(path, "rt");
    if (f == NULL) {
        termina("Non è stato possibile aprire il file");
    }
    int e;
    do {
        v[*size] = malloc(sizeof(Capitale));
        if (v[*size] == NULL){
            free(v);
            termina("Memoria insufficiente");
        }
        e = fscanf(f, "%ms %lf %lf", &(v[*size]->nome), &(v[*size]->longitudine), &(v[*size]->latitudine));
        if (e != EOF) {
            if (e != 3)
            {
                libera_capitali(v,*size);
                termina("contenuto illegale del file");
            }
            (*size)++;
            // caso in cui ho preso correttamente un numero
            if (maxSize == *size) {
                maxSize *= 2;
                v = realloc(v, maxSize * sizeof(Capitale*));
                if (v == NULL)
                    termina("Memoria insufficiente");
            }
        }else{
            if(v[*size]!=NULL){
                free(v[*size]->nome);
                free(v[*size]);
            }
        }
    } while (e != EOF);
    fclose(f);
    return v;
}

void stampaCapitaliVett(Capitale **v, int dimV){
    assert(v!=NULL);
    // stampo il contenuto dell'array
    for(int i = 0; i<dimV; i++){
        assert(v[i]!=NULL);
        printf("Capitale %s %lf %lf\n", v[i]->nome, v[i]->latitudine, v[i]->longitudine);
    }
}

// funzione di merge adattata dal merge di array di puntatori a capitali
void merge(Capitale **a, int na, 
Capitale **c, int nc,
Capitale **b)
{
    assert(a!=NULL);
    assert(c!=NULL);
    assert(b!=NULL);
    assert(na>0);
    assert(nc>0);

    int i=0; // indice per a[]
    int j=0; // indice per c[]
    int k=0; // indice per b[]

    // scorro a[] e c[] e copio il minore in b[]
    while(i<na && j<nc) {
        // guardo se il nome di a[i] è minore del nome c[j]
        // ordinamento lessicografico per nome
        // if( strcmp(a[i]->nome,c[j]->nome)<0 ) { 
        if( a[i]->latitudine < c[j]->latitudine ) {
            b[k] = a[i];
            i++;
        } else {
            b[k] = c[j];
            j++;
        }
        k++;
    }

    // copio il resto di a[] in b[]
    while(i<na) {
        b[k] = a[i];
        i++;
        k++;
    }

    // copio il resto di c[] in b[]
    while(j<nc) {
        b[k] = c[j];
        j++;
        k++;
    }
    assert(i==na);
    assert(j==nc);
    assert(k==na+nc); 
}


// funzione mergesort ricorsiva, adattata dal mergesort di capitali
void mergesort(Capitale **a, int n)
{
    assert(a!=NULL);
    assert(n>0);

    // caso base
    if(n==1) return;

    int n1 = n/2;     // dimensione prima parte
    int n2 = n - n1;  // dimensione seconda parte

    mergesort(a,n1);
    mergesort(a+n1,n2);

    // ho le due metà ordinate devo fare il merge
    Capitale **b = malloc(n*sizeof(*b));
    if(b==NULL) {
        libera_capitali(a,n);
        termina("malloc fallita nel merge");}
    merge(a,n1,&a[n1],n2,b); 
    // copio il risultato da b[] ad a[]
    for(int i=0;i<n;i++)
        a[i] = b[i];  // sto copiando dei puntatori 

    free(b);
}

int main(int argc, char const* argv[])
{
    int dim = 0;

    Capitale ** capitali;
    // TODO argv e free
    capitali = caricaCapitaliDaFile(argv[1], &dim);
    mergesort(capitali, dim);
    stampaCapitaliVett(capitali,dim);
    libera_capitali(capitali,dim);
    return 0;
}

void termina(const char* messaggio)
{
    if (errno != 0)
        perror(messaggio);
    else
        fprintf(stderr, "%s\n", messaggio);
    exit(1);
}