#define _GNU_SOURCE // avverte che usiamo le estensioni GNU
#include <assert.h> // permette di usare la funzione assert
#include <errno.h> // necessaria per usare errno
#include <stdbool.h> // gestisce tipo bool (per variabili booleane)
#include <stdio.h> // permette di usare scanf printf etc ...
#include <stdlib.h> // conversioni stringa/numero exit() etc ...
#include <string.h> // funzioni di confronto/copia/etc di stringhe

typedef struct {
    char* name;
    long size; // le dimensioni più grandi di un gb non riesce a catturarle l'int
} File;

File* creaFile(char* name);
void termina(const char* messaggio);
void stampaVett(File** v, int dimV);
void stampa_info_file(const File* a, FILE* f);
void libera_arr(File** a, int size);
void merge(File** a, int na, File** c, int nc, File** b);
void mergesort(File** a, int n);

int main(int argc, char* argv[])
{
    if (argc < 2) {
        printf("uso: %s nome1 [nome2 nome3]\n", argv[0]);
        exit(1);
    }
    File** files; // puntatore a puntatore perché ognu elemento dell'array è un puntatore a un file
    files = malloc((argc - 1) * sizeof(*files));
    if (files == NULL)
        termina("Memoria esaurita");
    int messi = 0; // num di elementi inseriti nel vettore files
    for (int i = 1; i < argc; i++) {
        files[messi] = creaFile(argv[i]);
        if (files[messi] != NULL)
            messi++;
    }
    mergesort(files, messi);
    stampaVett(files, messi);
    libera_arr(files, messi);
    return 0;
}

void stampa_info_file(const File* a, FILE* f)
{
    fprintf(f, "Nome file: %s\nDimensioni: %ld\n\n", a->name, a->size);
}

void stampaVett(File** v, int dimV)
{
    assert(v != NULL);
    // stampo il contenuto dell'array sul terminale
    for (int i = 0; i < dimV; i++) {
        stampa_info_file(v[i], stdout);
    }
}

void libera_arr(File** a, int size)
{
    for (int i = 0; i < size; i++) {
        free(a[i]->name);
        free(a[i]);
    }
    free(a);
}

// funzione di merge adattata dal merge di array di puntatori a File
void merge(File **a, int na, 
File **c, int nc,
File **b)
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
    if( a[i]->size < c[j]->size ) {
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


// funzione mergesort ricorsiva, adattata dal mergesort di File
void mergesort(File **a, int n)
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
  File **b = malloc(n*sizeof(*b));
  if(b==NULL) termina("malloc fallita nel merge");
  merge(a,n1,&a[n1],n2,b); 
  // copio il risultato da b[] ad a[]
  for(int i=0;i<n;i++)
    a[i] = b[i];  // sto copiando dei puntatori 

  free(b);
}

File* creaFile(char* file_name)
{
    assert(file_name != NULL);
    // ? ricordarsi che se sono file di testo metterci modalità rt per ricordarselo
    FILE* f = fopen(file_name, "r");
    if (f == NULL) {
        fprintf(stderr, "Errore, file %s non trovato", file_name);
        return NULL;
    }
    if (fseek(f, 0, SEEK_END) != 0) {
        fprintf(stderr, "Non sono riuscito a spostare correttamente il puntatore del file");
        fclose(f);
        return NULL;
    }

    long pos = ftell(f); // prendo il puntatore del file a che posizione è
    if (pos < 0) {
        fprintf(stderr, "Non è stato possibile riconoscere la posizione del puntatore sul file");
        fclose(f);
        return NULL;
    }

    File* a;
    a = malloc(sizeof(File));
    if (a == NULL)
        termina("Memoria insufficiente");
    a->name = strdup(file_name);
    a->size = pos;

    return a;
}

void termina(const char* messaggio)
{
    if (errno != 0)
        perror(messaggio);
    else
        fprintf(stderr, "%s\n", messaggio);
    exit(1);
}