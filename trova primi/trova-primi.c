#define _GNU_SOURCE // avverte che usiamo le estensioni GNU
#include <assert.h> // permette di usare la funzione assert
#include <errno.h> // necessaria per usare errno
#include <stdbool.h> // gestisce tipo bool (per variabili booleane)
#include <stdio.h> // permette di usare scanf printf etc ...
#include <stdlib.h> // conversioni stringa/numero exit() etc ...
#include <string.h> // funzioni di confronto/copia/etc di stringhe

/* Questo programma prende da 1 a n numeri e li inserisce in un array solo se sono primi*/

void termina(const char* messaggio)
{
    if (errno != 0)
        perror(messaggio);
    else
        fprintf(stderr, "%s\n", messaggio);
    exit(1);
}

bool isPrimo(int k)
{
    assert(k >= 2);
    for (int i = 2; i * i <= k; i++) {
        if (k % i == 0)
            return false;
    }
    return true;
}

int main()
{
    int n, messi=0;

    puts("dammi il numero limite dell'array");
    scanf("%d", &n);
    assert(n > 0);

    int* a = malloc(n * sizeof(int));
    if (a == NULL) {
        termina("malloc fallita");
    }

    for (int i = 2; i < n; i++) {
        if (isPrimo(i)){
            a[messi] = i; // ! con le quadre accede direttamente al valore, come se facessi *(a+messi) = n
            messi++;
        }
    }
    for (int i = 0; i < messi; i++) {
        printf("%d\n", a[i]);
    }
    isPrimo(4);
    return 0;
}
