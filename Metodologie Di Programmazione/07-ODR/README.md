# ODR (One Definition Rule)

## DRY (Don't Repeat Yourself)

Scrivere <u>una sola volta</u> le varie definizioni di classi e funzioni negli **header file**. \
Ecco le 4 regole principali della **ODR**:
1. Ogni unità di traduzione deve contenere non più di una definizione di una variabile, classe, funzione, enumerazione o template
2. Un programma deve contenere **esattamente una definizione** di ogni <u>variabile o funzione non-inline<u> dichiarate nel programma 