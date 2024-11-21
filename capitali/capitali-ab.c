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
  struct AlberoCapitale *sinistra;
  struct AlberoCapitale *destra;
} AlberoCapitale;

/*Leggere dal file capitali delle capitali con nome, latitudine e longitudine e
 * fare il mergesort per latitudine*/
void libera_capitali(AlberoCapitale *radice) {
  if (radice == NULL)
    return;
  libera_capitali(radice->sinistra);
  libera_capitali(radice->destra);
  free(radice->nome);
  free(radice);
}

/*
  insert(node_to_insert: NodoABR<T>, start: NodoABR<T> = this.root){
    if(start === null) return;
    if(start.v == node_to_insert.v) return;
    if(start.v < node_to_insert.v){
      if(start.right === null) start.right = node_to_insert;
      else this.insert(node_to_insert, start.right);
    } else{
      if(start.left === null) start.left = node_to_insert;
      else this.insert(node_to_insert, start.left);
    }
  }
*/
AlberoCapitale *crea_nodo(char *nome, double latitudine, double longitudine) {
  AlberoCapitale *node_to_insert = malloc(sizeof(AlberoCapitale));
  if (node_to_insert == NULL)
    termina("Memoria insufficiente\n");
  node_to_insert->destra = NULL;
  node_to_insert->sinistra = NULL;
  node_to_insert->nome = nome;
  node_to_insert->latitudine = latitudine;
  node_to_insert->longitudine = longitudine;
  return node_to_insert;
}

/*Aggiunge le capitali sull'albero prima a sinistra e poi a destra*/
void aggiungi_capitale(AlberoCapitale **radice, char *nome, double latitudine,
                       double longitudine) {
  if (*radice == NULL) {
    *radice = crea_nodo(nome, latitudine, longitudine);
    return;
  }
  if (strcmp((*radice)->nome, nome) == 0) {
    return; // il nodo è una ripetizione quindi esco
  }
  if (strcmp((*radice)->nome, nome) < 0) {
    if ((*radice)->destra == NULL) {
      (*radice)->destra = crea_nodo(nome, latitudine, longitudine);
      return;
    }
    aggiungi_capitale(&((*radice)->destra), nome, latitudine, longitudine);
  } else {
    if ((*radice)->sinistra == NULL) {
      (*radice)->sinistra = crea_nodo(nome, latitudine, longitudine);
      return;
    }
    aggiungi_capitale(&((*radice)->sinistra), nome, latitudine, longitudine);
  }
  return;
}

// questa funzione legge un file con all'interno una stringa e la carica in una
// lista di Capitale
void caricaCapitaliDaFile(const char *path, AlberoCapitale **radice) {

  // apertura del file
  FILE *f = fopen(path, "rt");
  if (f == NULL) {
    termina("Non è stato possibile aprire il file");
  }

  int e;
  while (true) {
    char *nome;
    double latitudine;
    double longitudine;
    e = fscanf(f, "%ms %lf %lf", &nome, &latitudine, &longitudine);
    if (e == EOF)
      break;
    if (e != 3) {
      free(nome);
      termina("contenuto illegale del file");
    }
    aggiungi_capitale(radice, nome, latitudine, longitudine);
  };
  fclose(f);
}

void stampaCapitali(AlberoCapitale *radice) {
  if (radice == NULL)
    return;
  printf("%s %lf %lf\n", radice->nome, radice->latitudine, radice->longitudine);
  stampaCapitali(radice->sinistra);
  stampaCapitali(radice->destra);
}

int main(int argc, char const *argv[]) {
  AlberoCapitale *radice = NULL;
  caricaCapitaliDaFile(argv[1], &radice);
  stampaCapitali(radice);
  libera_capitali(radice);
  return 0;
}

void termina(const char *messaggio) {
  if (errno != 0)
    perror(messaggio);
  else
    fprintf(stderr, "%s\n", messaggio);
  exit(1);
}