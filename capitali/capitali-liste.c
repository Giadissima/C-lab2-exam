#define _GNU_SOURCE  // avverte che usiamo le estensioni GNU
#include <assert.h>  // permette di usare la funzione assert
#include <errno.h>   // necessaria per usare errno
#include <stdbool.h> // gestisce tipo bool (per variabili booleane)
#include <stdio.h>   // permette di usare scanf printf etc ...
#include <stdlib.h>  // conversioni stringa/numero exit() etc ...
#include <string.h>  // funzioni di confronto/copia/etc di stringhe

void termina(const char *messaggio);

typedef struct Capitale {
  char *nome;
  double latitudine;
  double longitudine;
  struct Capitale *next;
} Capitale;
/*Leggere dal file capitali delle capitali con nome, latitudine e longitudine e
 * fare il mergesort per latitudine*/

void libera_capitali(Capitale *testa) {
  if(testa == NULL) return;
  libera_capitali(testa->next);
  free(testa->nome);
  free(testa);
}

void aggiungi_capitale_testa(Capitale **testa, char *nome, double latitudine,
                             double longitudine) {
  Capitale *newCapitale = malloc(sizeof(Capitale));
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
void aggiungi_capitale_ordinata_nome(Capitale **testa, char *nome, double latitudine,
                             double longitudine) {
   // Caso base: inserisci in testa se la lista è vuota o se il nuovo nodo va all'inizio
  if (*testa == NULL || strcmp(nome, (*testa)->nome) < 0) {
    Capitale *newCapitale = malloc(sizeof(Capitale));
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

// cancella tutti i nodi di una lista con latitudine > k
void cancellaCoordinate(Capitale ** testa, double k) // k= chiave di ricerca
{
  if((*testa)==NULL) return;
  if((*testa)->latitudine > k){
    Capitale *tmp = (*testa)->next;
    free((*testa)->nome);
    free((*testa));
    (*testa)=tmp;
  }
  if((*testa)->next!=NULL && (*testa)->next->latitudine > k){
    Capitale *tmp = (*testa)->next->next;
    free((*testa)->next->nome);
    free((*testa)->next);
    (*testa)->next=tmp;
  }
  cancellaCoordinate(&(*testa)->next, k);
}


// questa funzione legge un file con all'interno una stringa e la carica in una lista di Capitale
void caricaCapitaliDaFile(const char *path, Capitale ** testa) {
  
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

void stampaCapitali(Capitale *testa) {
  if(testa==NULL)
    printf("Lista delle capitali vuota, niente da visualizzare...");
  while(testa != NULL){
    printf("%s %lf %lf\n", testa->nome, testa->latitudine, testa->longitudine);
    testa = testa ->next;
  }
}

int main(int argc, char const *argv[]) {
  Capitale *testa=NULL;
  // TODO argv e free
  caricaCapitaliDaFile(argv[1], &testa);
  cancellaCoordinate(&testa, 47);
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