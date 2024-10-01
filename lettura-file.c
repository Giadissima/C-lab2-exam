#define _GNU_SOURCE   // avverte che usiamo le estensioni GNU 
#include <stdio.h>    // permette di usare scanf printf etc ...
#include <stdlib.h>   // conversioni stringa/numero exit() etc ...
#include <stdbool.h>  // gestisce tipo bool (per variabili booleane)
#include <assert.h>   // permette di usare la funzione assert
#include <string.h>   // funzioni di confronto/copia/etc di stringhe
#include <errno.h>    // necessaria per usare errno

void termina(const char *messaggio){
  if(errno!=0) perror(messaggio);
  else fprintf(stderr,"%s\n", messaggio);
  exit(1);
}

// questa funzione legge un file e carica un vettore contenente le righe
void leggi_file(char * path, int * v[], int * dimV, int *maxSize){
  *maxSize=10;
  if(*dimV != 0){
    free(v);
    *dimV=0;
  }
  *v = malloc(*maxSize*sizeof(int));
  FILE *f = fopen(path, "rt");
  if(f==NULL){
    termina("Non è stato possibile aprire il file");
  }
  int e;
  do{
    int n;
    e = fscanf(f, "%d", &n);
    if(e != EOF){
      if(e!=1) termina("contenuto illegale del file");
      // caso in cui ho preso correttamente un numero
      if(maxSize==dimV){
        *maxSize *= 2;
        *v = realloc(v, *maxSize*sizeof(int));
      }
      (*v)[*dimV]=n;
      (*dimV)++;

    }
  }while(e!=EOF);

}
// questa funzione legge un file e carica un vettore contenente i numeri contenenti nelle righe
// void leggi_file(char * path, int * v){


// }

void stampa_vett(int **v, int dimV){
  for(int i = 0; i<dimV; i++){
    printf("%d", &v[i]);
  }
}

int main(int argc, char const *argv[]) {
  char * file_path = "input.txt";
  int *v;
  int dimV=0;
  int sizeMax=0;
  leggi_file(file_path, v, &dimV, &sizeMax);

  return 0;
}