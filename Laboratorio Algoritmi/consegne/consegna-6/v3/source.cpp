#include <iostream>
#include <vector>
#include <string>

int somma(int a, int b) {
    return a + b;
}

int sottrazione(int a, int b) {
    return a - b;
}

int moltiplicazione(int a, int b) {
    return a * b;
}

double calcolaMedia(std::vector<int>& valori) {
    if (valori.empty()) {
        return 0.0;
    }

    int totale = 0;

    for (int valore : valori) {
        totale += valore;
    }

    return static_cast<double>(totale) / valori.size();
}

void stampaVettore(std::vector<int>& numeri) {
    std::cout << "Contenuto vettore: ";

    for (int numero : numeri) {
        std::cout << numero << " ";
    }

    std::cout << std::endl;
}

int trovaMassimo(std::vector<int>& numeri) {
    if (numeri.empty()) {
        return 0;
    }

    int massimo = numeri[0];

    for (int numero : numeri) {
        if (numero > massimo) {
            massimo = numero;
        }
    }

    return massimo;
}

int contaPari(std::vector<int>& numeri) {
    int conteggio = 0;

    for (int numero : numeri) {
        if (numero % 2 == 0) {
            conteggio++;
        }
    }

    return conteggio;
}

int main() {
    std::vector<int> dati;

    for (int i = 1; i <= 15; i++) {
        dati.push_back(i * 2);
    }

    stampaVettore(dati);

    int massimo = trovaMassimo(dati);
    double media = calcolaMedia(dati);
    int numeriPari = contaPari(dati);

    std::cout << "Massimo: " << massimo << std::endl;
    std::cout << "Media: " << media << std::endl;
    std::cout << "Pari: " << numeriPari << std::endl;

    int valoreA = 20;
    int valoreB = 5;

    std::cout << "Somma: "
              << somma(valoreA, valoreB)
              << std::endl;

    std::cout << "Differenza: "
              << sottrazione(valoreA, valoreB)
              << std::endl;

    std::cout << "Prodotto: "
              << moltiplicazione(valoreA, valoreB)
              << std::endl;

    std::string utente = "Mario";

    if (utente.length() >= 5) {
        std::cout << "Nome valido" << std::endl;
    } else {
        std::cout << "Nome troppo corto" << std::endl;
    }

    int indice = 0;

    while (indice < 3) {
        std::cout << "Ciclo numero "
                  << indice
                  << std::endl;

        indice++;
    }

    int totale = 0;

    for (size_t i = 0; i < dati.size(); i++) {
        totale += dati[i];
    }

    std::cout << "Totale elementi: "
              << totale
              << std::endl;

    bool presente = false;

    for (int numero : dati) {
        if (numero == 16) {
            presente = true;
            break;
        }
    }

    if (presente) {
        std::cout << "Elemento trovato" << std::endl;
    } else {
        std::cout << "Elemento assente" << std::endl;
    }

    return 0;
}