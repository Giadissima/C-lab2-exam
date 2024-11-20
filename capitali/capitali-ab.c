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
  if(radice == NULL) return;
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

/*Aggiunge le capitali sull'albero prima a sinistra e poi a destra*/
void aggiungi_capitale(AlberoCapitale **radice, char *nome, double latitudine,
                             double longitudine) {
  if(radice == NULL) return; 
    if(strcmp((*radice)->nome, nome) == 0) return; // il nodo è una ripetizione quindi esco
    if(strcmp((*radice)->nome, nome) < 0){
      if((*radice)->destra == NULL) (*radice)->destra = node_to_insert;
      else this.insert(node_to_insert, (*radice)->destra);
    } else{
      if((*radice)->left === null) (*radice)->left = node_to_insert;
      else this.insert(node_to_insert, (*radice)->left);
    }
    return;
  }

  while(radice->sinistra)
}



// aggiunta di un elemento in maniera ordinata in una lista per nome
void aggiungi_capitale_ordinata_nome(AlberoCapitale **radice, char *nome, double latitudine,
                             double longitudine) {
   // Caso base: inserisci in testa se la lista è vuota o se il nuovo nodo va all'inizio
  if (*radice == NULL || strcmp(nome, (*radice)->nome) < 0) {
    AlberoCapitale *newCapitale = malloc(sizeof(AlberoCapitale));
    newCapitale->nome = nome;
    newCapitale->latitudine = latitudine;
    newCapitale->longitudine = longitudine;
    newCapitale->sinistra = *radice;
    *radice = newCapitale;
    return;
  }

  // Ricorsione per trovare la posizione corretta
  // Se il nome corrente nella lista è minore del nuovo nome, continua a cercare
  aggiungi_capitale_ordinata_nome(&(*radice)->sinistra, nome, latitudine, longitudine);
}


// questa funzione legge un file con all'interno una stringa e la carica in una lista di Capitale
void caricaCapitaliDaFile(const char *path, AlberoCapitale ** radice) {
  
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
      aggiungi_capitale(radice, nome, latitudine, longitudine);
  };
  fclose(f);
}

void stampaCapitali(AlberoCapitale *radice) {
  if(radice == NULL) return;
  printf("%s %lf %lf\n", radice->nome, radice->latitudine, radice->longitudine);
  stampaCapitali(radice->sinistra);
  stampaCapitali(radice->destra);
  
}

int main(int argc, char const *argv[]) {
  AlberoCapitale *radice=NULL;
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