# GDB

Uso di gdb per debuggare file .c

## Avvio del programma

Possiamo avviare il programma con gdb compilando il file .c con gcc con l'opzione -g, successivamente possiamo eseguire il seguente codice:

```bash
(gdb) eseguibile
```

## Aggiungere argomenti

Se avviando gdb in questo modo non funziona:

```bash
(gdb) eseguibile argomenti
```

oppure

```bash
(gdb) --args eseguibile argomenti
```

Allora prova così (soluzione sicura):

```bash
(gdb) eseguibile
(gdb) set args argomenti
```

## Creazione dei breakpoint

In qualsiasi momento ma soprattutto da fare come prima operazione, per poter debuggare è necessario mettere dei breakpoint

```bash
(gdb) break main
```

Successivamente dobbiamo arrivare al nostro primo breakpoint avviando il programma e eseguendo il comando continue

```bash
(gdb) run
(gdb) c
```

## Comandi per l'esecuzione del debug

### Istruzione successiva

Se digitiamo

```bash
(gdb) n
```

passiamo all'istruzione successiva

### Stampa valore di una variabile

Per controllare i valori delle variabili in quell'istante dobbiamo fare

```bash
(gdb) print a
(gdb) print b
```

### Monitorare delle variabili

Se vuoi controllare come cambia nel tempo una variabile senza ogni volta digitare **print** basta digitare i seguenti comandi.

#### Monitorare una variabile

Con questo comando aggiungi in alto nel terminale il label della variabile con il suo valore che sarà sempre visibile.

```bash
(gdb) display variabile
```

#### Visualizzare tutte le variabili monitorate

Per avere più informazioni dettagliate su tutte le variabili che stai monitorando puoi fare

```bash
(gdb) info display
```

#### Togliere il monitoraggio di una variabile

Per smettere di monitorare una variabile basta fare

```bash
(gdb) undisplay variabile
```

#### Aggiungere un watchpoint

Se vuoi che il programma si fermi ogni volta che una variabile viene cambiata puoi aggiungere quello che si chiama watchpoint

```bash
(gdb) watch variabile
```

### Visualizzare più istruzioni dal source code

Per poter visualizzare quando si esegue un continue o un step-forward più righe di codice invece di una soltanto possiamo usare il comando

```bash
(gdb) layout src
```
