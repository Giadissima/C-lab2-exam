#define _GNU_SOURCE // avverte che usiamo le estensioni GNU
#include <assert.h> // permette di usare la funzione assert
#include <errno.h> // necessaria per usare errno
#include <stdbool.h> // gestisce tipo bool (per variabili booleane)
#include <stdio.h> // permette di usare scanf printf etc ...
#include <stdlib.h> // conversioni stringa/numero exit() etc ...
#include <string.h> // funzioni di confronto/copia/etc di stringhe

void termina(const char* messaggio);

typedef struct Capitale{
    char* nome;
    double latitudine;
    double longitudine;
    struct Capitale * next=NULL; 
} Capitale;
/*Leggere dal file capitali delle capitali con nome, latitudine e longitudine e fare il mergesort per latitudine*/

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
        if (v[*size] == NULL)
            termina("Memoria insufficiente");
        e = fscanf(f, "%ms %lf %lf", &(v[*size]->nome), &(v[*size]->longitudine), &(v[*size]->latitudine));
        if (e != EOF) {
            if (e != 3)
            {
                printf("%s",v[*size]->nome);
                termina("contenuto illegale del file");
            }
            else puts("sto prendendo una riga correttamente");
            (*size)++;
            // caso in cui ho preso correttamente un numero
            if (maxSize == *size) {
                maxSize *= 2;
                v = realloc(v, maxSize * sizeof(Capitale*));
                if (v == NULL)
                    termina("Memoria insufficiente");
            }
        }
    } while (e != EOF);
    fclose(f);
    return v;
}

int main(int argc, char const* argv[])
{
    int dim = 0;
    caricaCapitaliDaFile("../capitali.txt", &dim);
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