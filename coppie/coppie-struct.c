// l'es consiste nel definire una struct coppia di due numeri, e scrivere le
// coppie ordinate per ordine della somma tra di due numeri
#define _GNU_SOURCE   // avverte che usiamo le estensioni GNU 
#include <stdio.h>    // permette di usare scanf printf etc ...
#include <stdlib.h>   // conversioni stringa/numero exit() etc ...
#include <stdbool.h>  // gestisce tipo bool (per variabili booleane)
#include <assert.h>   // permette di usare la funzione assert
#include <string.h>   // funzioni di confronto/copia/etc di stringhe
#include <errno.h>    // necessaria per usare errno


typedef struct
{
  int primo;
  int secondo;
}coppia;

void termina(const char *messaggio);
void aggiungi_coppia(coppia *v, int *dim, char * primo, char * secondo);
void stampa_coppie(coppia *v, int messi);
void merge(coppia *a, int na, 
           coppia *c, int nc,
           coppia *b);
void mergesort(coppia a[], int n);


int main(int argc, char *argv[]) {
  int maxSize=10; // # elementi dell'array a
  coppia *v;
  v = malloc(maxSize*sizeof(coppia));
  if(v==NULL)
    termina("Memoria insufficiente");
  int messi=0;

  if(argc == 1){
    char * mess;
    asprintf(&mess, "uso: ./%s <num_1> <num_2> [<num_1> <num_2> ...]", argv[0]);
  termina(mess);
  }

  for(int i=1; i<argc-1; i+=2){
    aggiungi_coppia(v, &messi, argv[i], argv[i+1]);
  }

  mergesort(v,messi);
  stampa_coppie(v, messi);

  return 0;
}

void termina(const char *messaggio){
  if(errno!=0) perror(messaggio);
  else fprintf(stderr,"%s\n", messaggio);
  exit(1);
}

void aggiungi_coppia(coppia *v, int *dim, char * primo, char * secondo){
  v[*dim].primo=atoi(primo);
    v[*dim].secondo=atoi(secondo);
    (*dim)++;
}

void stampa_coppie(coppia *v, int messi){
  for(int i=0; i<messi; i++){
    printf("(%d, %d)\n", v[i].primo, v[i].secondo);
  }
}

// funzione di merge adattata dal merge di array di coppie
void merge(coppia *a, int na, 
coppia *c, int nc,
coppia *b)
{
  assert(a!=NULL);
  assert(c!=NULL);
  assert(b!=NULL);
  assert(na>0);
  assert(nc>0);

  int i=0; // indice per a[]
  int j=0; // indice per c[]
  int k=0; // indice per b[]

  // scorro a[] e c[] e copio il minore in b[]
  while(i<na && j<nc) {
    // guardo se il nome di a[i] è minore del nome c[j]
    // ordinamento lessicografico per nome
    // if( strcmp(a[i]->nome,c[j]->nome)<0 ) { 
    if( (a[i].primo + a[i].secondo)  <  (c[j].primo + c[j].secondo)  ) { // ordinmento per lat decrescente 
      b[k] = a[i];
      i++;
    } else {
      b[k] = c[j];
      j++;
    }
    k++;
  }

  // copio il resto di a[] in b[]
  while(i<na) {
    b[k] = a[i];
    i++;
    k++;
  }

  // copio il resto di c[] in b[]
  while(j<nc) {
    b[k] = c[j];
    j++;
    k++;
  }
  assert(i==na);
  assert(j==nc);
  assert(k==na+nc); 
}


// funzione mergesort ricorsiva, adattata dal mergesort di interi
// è stato sufficiente modificare il tipo da int -> capitale * 
void mergesort(coppia *a, int n)
{
  assert(a!=NULL);
  assert(n>0);

  // caso base
  if(n==1) return;

  int n1 = n/2;     // dimensione prima parte
  int n2 = n - n1;  // dimensione seconda parte

  mergesort(a,n1);
  mergesort(a+n1,n2);

  // ho le due metà ordinate devo fare il merge
  coppia *b = malloc(n*sizeof(*b));
  if(b==NULL) termina("malloc fallita nel merge");
  merge(a,n1,&a[n1],n2,b); 
  // copio il risultato da b[] ad a[]
  for(int i=0;i<n;i++)
    a[i] = b[i];  // sto copiando dei puntatori 

  free(b);
}