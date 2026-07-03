Finire di capire come sviluppare la funzione di Needleman-Wunsch per calcolare
lo score di due blocchi.
Il problema che sto avendo in questo momento e' che non capisco come scorrere i nodi dell'albero
e confrontare i token dei nodi.
L'idea sarebbe quella di arrivare fino ad un nodo figlio e
chiamare l'algoritmo di Neddleman-Wunsch classico per
calcolare la matrice e fare il traceback. Dopodiche' una volta terminato continuare con 
il secondo figlio e via cosi. L'ordine dovrebbe essere topologico (ovvero controllo e scrivo in ordine di lettura dei nodi).