#define _GNU_SOURCE // avverte che usiamo le estensioni GNU
#include <assert.h> // permette di usare la funzione assert
#include <errno.h> // necessaria per usare errno
#include <stdbool.h> // gestisce tipo bool (per variabili booleane)
#include <stdio.h> // permette di usare scanf printf etc ...
#include <stdlib.h> // conversioni stringa/numero exit() etc ...
#include <string.h> // funzioni di confronto/copia/etc di stringhe

/*
Esercizio 2 Scrivere un programma triangolo che invocato scrivendo:

triangolo nomefile
legge da nomefile le stringhe contenute in esso e le salva in un array. Successivamente crea un file nomefile.triangolo contenente nella riga i-esima le parole dalla i-esima alla prima in ordine inverso. Ad esempio, se il file di input si chiama moria e contiene le parole dite amici ed entrate il file di output deve chiamarsi moria.triangolo e contentere le 4 righe:

dite
amici dite
ed amici dite
entrate ed amici dite
L'esercizio verrà considerato corretto solamente se la memoria verrà gestita in maniera dinamica e correttamente deallocata (verrà utilizzato valgrind per la verifica).

ATTENZIONE: i nome degli eseguibili (tabelline e triangolo) e i nomi dei file di output devono essere quelli indicati.*/
void termina(const char* messaggio);

// questa funzione legge un file con all'interno una stringa e la carica in un vettore dinamico di caratteri
char** caricaStrDaFile(char* path, int* size)
{ // size va passata per riferimento
    *size = 0;
    int maxSize = 10;
    assert(path!=NULL); // caso in cui non è stata allocata la stringa corrispondente al file path

    // array di puntatori a stringhe
    char** v = malloc(maxSize * sizeof(char*));
    if (v == NULL)
        termina("Memoria insufficiente");

    FILE* f = fopen(path, "rt");
    if (f == NULL) {
        termina("Non è stato possibile aprire il file");
    }

    // la nostra parola verrà memorizzato in un buffer
    int e;
    do {
        // uso di un buffer temporaneo per leggere la stringa
        e = fscanf(f, "%ms", &(v[*size]));
        if (e != EOF) {
            if (e != 1)
                termina("contenuto illegale del file");

            // Espansione dell'array se necessario
            if (maxSize == *size) {
                maxSize *= 2;
                v = realloc(v, maxSize * sizeof(char*));
                if (v == NULL)
                    termina("Memoria insufficiente");
            }

            // Allocazione di memoria per la stringa e copia del contenuto dal buffer
            if (v[*size] == NULL)
                termina("Memoria insufficiente");

            (*size)++;
        } else{
          if(v[*size]!=NULL){
                free(v[*size]);
            }
        }
    } while (e != EOF);

    fclose(f);
    return v;
}

void crea_triangolo(char** v, int n)
{
    assert(v != NULL); // il vettore deve essere allocato correttamente
    assert(n > 0);
    // Questo for serve per scrivere riga per riga
    for (int i = 0; i < n; i++) {
        // questo for serve per scrivere il necessario di una riga
        for (int j = 0; j <= i; j++) {
            printf("%s ", v[i - j]);
        }
        // per creare una nuova riga vado a capo con puts
        puts("");
    }
}

int main(int argc, char* argv[])
{

    // nel caso non è stato passato il numero di argomenti valido, esco
    if (argc != 2) {
        printf("uso: ./%s <file_path>\n", argv[0]);
        exit(1);
    }
    int size = 0;
    // siccome v deve puntare a delle stringhe, il suo tipo sarà puntatore di puntatore a char
    char** v = caricaStrDaFile(argv[1], &size);
    crea_triangolo(v, size);

    // Libera la memoria
    for (int i = 0; i < size; i++) {
        free(v[i]);
    }
    free(v);

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
