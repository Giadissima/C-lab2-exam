#define _GNU_SOURCE  // avverte che usiamo le estensioni GNU
#include <assert.h>  // permette di usare la funzione assert
#include <errno.h>   // necessaria per usare errno
#include <stdbool.h> // gestisce tipo bool (per variabili booleane)
#include <stdio.h>   // permette di usare scanf printf etc ...
#include <stdlib.h>  // conversioni stringa/numero exit() etc ...
#include <string.h>  // funzioni di confronto/copia/etc di stringhe

void termina(const char *messaggio);

typedef struct AlberoCapitale {
  char *nome;
  double latitudine;
  double longitudine;
  struct AlberoCapitale *next;
} AlberoCapitale;
/*Leggere dal file capitali delle capitali con nome, latitudine e longitudine e
 * fare il mergesort per latitudine*/

void libera_capitali(AlberoCapitale *testa) {
  if(testa == NULL) return;
  libera_capitali(testa->next);
  free(testa->nome);
  free(testa);
}

void aggiungi_capitale(AlberoCapitale **testa, char *nome, double latitudine,
                             double longitudine) {
  AlberoCapitale *newCapitale = malloc(sizeof(AlberoCapitale));
  newCapitale->nome = nome;
  newCapitale->latitudine= latitudine;
  newCapitale->longitudine=longitudine;
  if (*testa == NULL) {
    *testa=newCapitale;
    newCapitale->next=NULL;
  } else{
    newCapitale->next=*testa;
    *testa=newCapitale;
  }
}


// aggiunta di un elemento in maniera ordinata in una lista per nome
void aggiungi_capitale_ordinata_nome(AlberoCapitale **testa, char *nome, double latitudine,
                             double longitudine) {
   // Caso base: inserisci in testa se la lista è vuota o se il nuovo nodo va all'inizio
  if (*testa == NULL || strcmp(nome, (*testa)->nome) < 0) {
    AlberoCapitale *newCapitale = malloc(sizeof(AlberoCapitale));
    newCapitale->nome = nome;
    newCapitale->latitudine = latitudine;
    newCapitale->longitudine = longitudine;
    newCapitale->next = *testa;
    *testa = newCapitale;
    return;
  }

  // Ricorsione per trovare la posizione corretta
  // Se il nome corrente nella lista è minore del nuovo nome, continua a cercare
  aggiungi_capitale_ordinata_nome(&(*testa)->next, nome, latitudine, longitudine);
}


// questa funzione legge un file con all'interno una stringa e la carica in una lista di Capitale
void caricaCapitaliDaFile(const char *path, AlberoCapitale ** testa) {
  
  // apertura del file
  FILE *f = fopen(path, "rt");
  if (f == NULL) {
    termina("Non è stato possibile aprire il file");
  }

  int e;
  while(true) {
    char *nome;
    double latitudine;
    double longitudine;
    e = fscanf(f, "%ms %lf %lf", &nome, &latitudine, &longitudine);
    if (e == EOF) break;
      if (e != 3) {
        free(nome);
        termina("contenuto illegale del file");
      }
      aggiungi_capitale_ordinata_nome(testa, nome, latitudine, longitudine);
  };
  fclose(f);
}

void stampaCapitali(AlberoCapitale *testa) {
  if(testa==NULL)
    printf("Lista delle capitali vuota, niente da visualizzare...");
  while(testa != NULL){
    printf("%s %lf %lf\n", testa->nome, testa->latitudine, testa->longitudine);
    testa = testa ->next;
  }
}

int main(int argc, char const *argv[]) {
  AlberoCapitale *testa=NULL;
  // TODO argv e free
  caricaCapitaliDaFile(argv[1], &testa);
  stampaCapitali(testa);
  libera_capitali(testa);
  return 0;
}

void termina(const char *messaggio) {
  if (errno != 0)
    perror(messaggio);
  else
    fprintf(stderr, "%s\n", messaggio);
  exit(1);
}