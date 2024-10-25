#define _GNU_SOURCE // avverte che usiamo le estensioni GNU
#include <assert.h> // permette di usare la funzione assert
#include <errno.h> // necessaria per usare errno
#include <stdbool.h> // gestisce tipo bool (per variabili booleane)
#include <stdio.h> // permette di usare scanf printf etc ...
#include <stdlib.h> // conversioni stringa/numero exit() etc ...
#include <string.h> // funzioni di confronto/copia/etc di stringhe

/*Esercizio 1 Scrivere un programma tabelline che invocato scrivendo

tabelline n1 n2 n2 ....
per ogni intero N sulla linea di comando crea il file N.tab contenente la tabellina (i multipli da 1 a 10) del numero N. Ad esempio scrivendo

tabelline 4 20
deve essere creato il file 4.tab contenente la sequenza

4
8
12
16
20
24
28
32
36
40
ed il file 20.tab contenente la sequenza

20
40
60
80
100
120
140
160
180
200
I file di output devono chiamarsi esattamente come indicato, e contenere esattamente i valori richiesti con un valore su ogni riga. Il programma deve accettare un qualsiasi numero di argomenti sulla linea di comando. Verificate con valgrind il corretto uso e deallocazione della memoria*/

void termina(const char* messaggio);

void crea_tabella(char* n)
{
    char* filepath;
    int n1 = atoi(n);
    if (n1 == 0) {
        puts("ATTENZIONE, 0 trovato, genererò la tabellina di 0, sei sicuro di non aver immesso un dato sbagliato come parametro?"); // ? la funzione atoi restituisce 0 se non è riuscito a convertire n in n1, perciò scrivo un warning dato che è inutile fare la tabellina di zero
    }
    asprintf(&filepath, "%d.tab", n1); // Crea il nome del file
    FILE* f = fopen(filepath, "w"); // Usa fopen per creare/aprire il file
    if (f == NULL) {
        perror("Errore nell'aprire il file");
        free(filepath);
        exit(1);
    }

    for (int i = 1; i < 10; i++) {
        fprintf(f, "%d\n", n1 * i); // Scrive nel file
    }
}

int main(int argc, char* argv[])
{
    // nel caso non è stato passato il numero di argomenti valido, esco
    if (argc == 1) {
        printf("uso: ./%s <num_1> <num_2> [<num_1> <num_2> ...]", argv[0]);
        exit(1);
    }

    // questo for richiama la funzione della creazione delle tabelline per ogni input passato da linea di comando
    for (int i = 0; i < argc - 1; i++) {
        crea_tabella(argv[i + 1]);
        printf("tabellina di %s generata\n", argv[i+1]);
    }

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