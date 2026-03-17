# Analisi dataset

Dividere il problema in 3 sottoproblemi:

- **Parte iniziziale**: dove i dati hanno poca varianza
- **Parte intermedia**: dove i valori iniziano ad avere rumore e hanno un valore grande (percio' evitare algoritmi simili al counting-sort)
- **Parte finale**: i dati hanno tantissimo rumore

I dati hanno un caratteristica particolare, ovvero, ogni 30 valori avviene un cambiamento drastico.

# Prima fase: Bucket-sort

## Primo prompt dato a chatgpt

```
ho un esercizio da fare che riguarda l'ordinamento di dati con un certo pattern (allego l'immagine del grafico dei dati).
Siccome devo fare l'analisi dei dati, ho pensato bene di dividere il problema iniziale in 3 sottoproblemi: la prima parte dove i dati variano poco tra di loro, la parte in mezzo dove i valori iniziano ad avere u po' di rumore e sono molto grandi, e la parte finale dove ce'e una grosso rumore dei dati.

Per valutare l'algoritmo migliore da utilizzare escludendo counting-sort, merge-sort, insertion-sort e quick-sort ho pensato per la prima parte dei dati dove la variazione dei dati e poca (signfica che i dati si ripetono molto) degli algoritmi che sono efficienti nella lettura nel leggere molti valori ripetuti (devono essere efficienti nelle letture nell'array).

Mentre nella prima parte centrale i valori sono molto alti (arrivano fino a 10500), percio' e' da evitare di utilizzare array come counting-sort dove il valore massimo dell'array fa la differenza su tutto l'array. Qui sarebbe bene utilizzare un algoritmo (sempre escludendo counting-sort, merge-sort, insertion-sort e quick-sort) che sia ottimo nell'ordinare valori che variano leggermente di piu' della parte iniziale ma che hanno valori estremamente alti.

Nell'ultima parte invece abbiamo una situazione particolare, ovvero i dati sono ordinati al contrario (quasi) ed hanno un sacco di rumore. Percio' utilizzerei delgi algoritmi che sono molto efficienti nel leggere valori che variano molto tra di loro e che sono quasi ordinati al contrario.
```

Seguendo il consiglio di **chatgpt** mi sono messo a guardare **BucketSort** e sembra ottimo con i valori ripetuti ma se non implementato bene *non lavora con i numeri negativi* (qui il primo problema da affrontare). Devo modificare l'algoritmo in modo tale che sia utilizzabile anche per numeri negativi (normalizzazione dell'inidice ?).

Prossima valutazione: **RadixSort**

