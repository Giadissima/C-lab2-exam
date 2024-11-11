#define _GNU_SOURCE   // avverte che usiamo le estensioni GNU 
#include <stdio.h>    // permette di usare scanf printf etc ...
#include <stdlib.h>   // conversioni stringa/numero exit() etc ...
#include <stdbool.h>  // gestisce tipo bool (per variabili booleane)
#include <assert.h>   // permette di usare la funzione assert
#include <string.h>   // funzioni di confronto/copia/etc di stringhe

// da compilare con:
//  gcc -std=c11 -Wall -O -g -o parametri  parametri.c


// Nota: per eseguire le stampe di interi e puntatori
// questi vengono tutti convertiti in long e 
// stampati usando il formato %ld in printf
// (%ld si usa infatti per stamnpare i long)  


// funzione che incrementa di 1 un parametro
// passato per valore
int incrementa1(int z)
{
  printf("incrementa1: z si trova nella posizione %ld e vale %ld\n",
         (long) &z, (long )z);  
  z +=1;
  return 0;
}

// funzione che incrementa di 1 un parametro 
// passato per riferimento attraverso un puntatore
int incrementa1p(int *p)
{
  printf("incrementa1p: p si trova nella posizione %ld e vale %ld\n",
         (long) &p, (long) p);  
  *p +=1;
  return 0;
}


int main(int argc, char *argv[])
{
  int n =5;
  
  printf("main 1: n si trova nella posizione %ld e vale %ld\n",
         (long) &n, (long )n);  
  incrementa1(n);    // chiamata per valore: non ha effetto su n
  printf("main 2: n si trova nella posizione %ld e vale %ld\n",
         (long) &n, (long )n);  
  incrementa1p(&n);  // chiamata per riferimento: modifica n
  printf("main 3: n si trova nella posizione %ld e vale %ld\n",
         (long) &n, (long )n);  
  return 0;
}