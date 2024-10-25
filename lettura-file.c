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

// questa funzione legge un file con all'interno dei numeri e li carica in un vettore dinamico
int* caricaIntDaFile(char * path, int *size){
  *size=0;
  int maxSize=10;
  
  int *v = malloc(maxSize*sizeof(int));
  if(v==NULL)
    termina("Memoria insufficiente");
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
      if(maxSize==*size){
        maxSize *= 2;
        v = realloc(v, maxSize*sizeof(int));
        if(v==NULL)
          termina("Memoria insufficiente");
      }
      v[*size]=n;
      (*size)++;

    }
  }while(e!=EOF);
  return v;

}

// questa funzione legge un file con all'interno una stringa e la carica in un vettore dinamico di caratteri
char* caricaStrDaFile(char * path, int *size){ // size va passata per riferimento
  *size=0;
  int maxSize=10;

  char *v = malloc(maxSize*sizeof(int));
  if(v==NULL)
    termina("Memoria insufficiente");
  FILE *f = fopen(path, "rt");
  if(f==NULL){
    termina("Non è stato possibile aprire il file");
  }
  int e;
  do{
    int n;
    e = fscanf(f, "%c", &n);
    if(e != EOF){
      if(e!=1) termina("contenuto illegale del file");
        // caso in cui ho preso correttamente un numero
        if(maxSize==*size){
          maxSize *= 2;
          v = realloc(v, maxSize*sizeof(int));
          if(v==NULL)
            termina("Memoria insufficiente");
          }
      v[*size]=n;
      (*size)++;

    }
  }while(e!=EOF);
  return v;
}

void stampaIntVett(int *v, int dimV){
  assert(v!=NULL);
  // stampo il contenuto dell'array
  for(int i = 0; i<dimV; i++){
    printf("%do numero: %d\n",i, v[i]);
  }
}

void stampaCharVett(char *v, int dimV){
  assert(v!=NULL);
  // stampo il contenuto dell'array
  for(int i = 0; i<dimV; i++){
    printf("%c",v[i]);
  }
puts("\n");
}

int main() {
  char * file_path = "input2.txt";
  int size=0;
  char *v = caricaStrDaFile(file_path, &size);
  stampaCharVett(v, size);

  return 0;
}
