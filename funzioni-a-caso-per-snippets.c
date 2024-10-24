#define _GNU_SOURCE   // avverte che usiamo le estensioni GNU 
#include <stdio.h>    // permette di usare scanf printf etc ...
#include <stdlib.h>   // conversioni stringa/numero exit() etc ...
#include <stdbool.h>  // gestisce tipo bool (per variabili booleane)
#include <assert.h>   // permette di usare la funzione assert
#include <string.h>   // funzioni di confronto/copia/etc di stringhe
#include <errno.h>    // necessaria per usare errno

void termina(const char *messaggio);
bool is_greater_string(char * a, char * b);

int main(int argc, char const *argv[]) {
  if(is_greater_string("c", "b")){
    puts("a > b");
  }else{
    puts("b>a");
  }
  return 0;
}


void termina(const char *messaggio){
  if(errno!=0) perror(messaggio);
  else fprintf(stderr,"%s\n", messaggio);
  exit(1);
}

bool is_greater_string(char * a, char * b){
  return strcmp(a,b)==1;
}