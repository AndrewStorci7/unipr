## Esercizio 1

Dato il file `andamento_vendite_marketing.csv` estrarre i dati delle varie colonne e calcoalre i seguenti dati:
- Profitto di ogni giorno e ogni singolo dato salvarlo in un'array
- Profitto medio
- Quale tipologia di prodotto e' stata venduita di pii' per ogni giorno
- Quale tipologia di prodotto e' stat venduta di piu' in assoluto

<!-- ### Soluzione

# 1. Inizializziamo le variabili che ci serviranno
profitti = []
totale_std = 0
totale_prem = 0
totale_lux = 0

# Apriamo il file in modalità lettura
with open("andamento_vendite_marketing.csv", "r") as file:
    # Saltiamo l'intestazione
    intestazione = next(file)
    
    for riga in file:
        # Puliamo la riga e dividiamo i dati
        dati = riga.strip().split(",")
        
        # Estraiamo i valori (ricordati di convertirli in numeri!)
        data = dati[0]
        incasso = float(dati[1])
        spese = float(dati[2])
        qty_std = int(dati[3])
        qty_prem = int(dati[4])
        qty_lux = int(dati[5])
        
        # --- TASK 1: Calcolo Profitto Giornaliero ---
        profitto_del_giorno = incasso - spese
        profitti.append(profitto_del_giorno)
        
        # --- TASK 3: Prodotto più venduto del giorno ---
        # Creiamo un piccolo dizionario temporaneo per confrontarli facilmente
        vendite_giorno = {
            "Standard": qty_std,
            "Premium": qty_prem,
            "Luxury": qty_lux
        }
        # Troviamo la chiave con il valore massimo
        prodotto_top_giorno = max(vendite_giorno, key=vendite_giorno.get)
        print(f"Giorno {data}: Il prodotto più venduto è {prodotto_top_giorno} ({max(vendite_giorno.values())} pezzi)")
        
        # --- PREPARAZIONE TASK 4: Accumuliamo i totali ---
        totale_std += qty_std
        totale_prem += qty_prem
        totale_lux += qty_lux

# --- TASK 2: Profitto Medio ---
profitto_medio = sum(profitti) / len(profitti)

# --- TASK 4: Prodotto più venduto in assoluto ---
totale_assoluto = {
    "Standard": totale_std,
    "Premium": totale_prem,
    "Luxury": totale_lux
}
vincitore_assoluto = max(totale_assoluto, key=totale_assoluto.get)

# --- STAMPA DEI RISULTATI FINALI ---
print("-" * 40)
print(f"PROFITTO MEDIO MENSILE: {profitto_medio:.2f}€")
print(f"PRODOTTO PIÙ VENDUTO IN ASSOLUTO: {vincitore_assoluto} con {totale_assoluto[vincitore_assoluto]} pezzi.")
print(f"LISTA TUTTI PROFITTI: {profitti}")

-->