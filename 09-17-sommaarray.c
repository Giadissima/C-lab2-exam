#define _GNU_SOURCE // avverte che usiamo le estensioni GNU
#include <assert.h> // permette di usare la funzione assert
#include <stdbool.h> // gestisce tipo bool (per variabili booleane)
#include <stdio.h> // permette di usare scanf printf etc ...
#include <stdlib.h> // conversioni stringa/numero exit() etc ...
#include <string.h> // funzioni di confronto/copia/etc di stringhe

int main(int argc, char *argv[])
{
    int *a, somma = 0, n;

    do {
        puts("dammi il numero di elementi da sommare");
        int e = scanf("%d", &n);
        if (e != 1) {
            puts("numero inserito non valido");
            exit(1);
        }
        if (n < 1) {
            puts("il numero di elementi non può essere negativo");
            exit(2);
        }
        if (n > 1000) {
            puts("hai inserito troppi elementi!");
        }
    } while (n > 1000);

    a = malloc(n * sizeof(int));
    if (a == NULL) {
        puts("Malloc fallita");
        exit(3);
    }
    for (int i = 0; i < n; i++) {
        printf("inserire il %do numero", i + 1);
        int e = scanf("%d", &a[i]);
        if (e != 1) {
            puts("numero inserito non valido!");
            i--;
        }
    }

    for (int i = 0; i < n; i++) {
        somma += a[i];
    }
    printf("La somma totale è %d\n", somma);

    free(a);
    return 0;
}