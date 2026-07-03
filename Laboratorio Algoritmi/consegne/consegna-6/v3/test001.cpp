#include <iostream>
#include <cstring>

int somma(int x, int y)
{
    return x + y;
}

int sottrai(int x, int y)
{
    return x - y;
}

int moltiplica(int x, int y)
{
    return x * y;
}

double calcolaMedia(int valori[], int n)
{
    if (n == 0)
    {
        return 0.0;
    }

    int sommaValori = 0;

    for (int i = 0; i < n; i++)
    {
        sommaValori += valori[i];
    }

    return (double)sommaValori / n;
}

void stampaValori(int valori[], int n)
{
    std::cout << "Valori: ";

    for (int i = 0; i < n; i++)
    {
        std::cout << valori[i] << " ";
    }

    std::cout << std::endl;
}

int massimo(int valori[], int n)
{
    if (n <= 0)
    {
        return 0;
    }

    int max = valori[0];

    for (int i = 1; i < n; i++)
    {
        if (valori[i] > max)
        {
            max = valori[i];
        }
    }

    return max;
}

int main()
{
    int DIMENSIONE = 10;

    int numeri[DIMENSIONE];

    for (int i = 0; i < DIMENSIONE; i++)
    {
        numeri[i] = (i + 1) * 5;
    }

    stampaValori(numeri, DIMENSIONE);

    int valoreMassimo = massimo(numeri, DIMENSIONE);
    double media = calcolaMedia(numeri, DIMENSIONE);

    std::cout << "Massimo: "
              << valoreMassimo
              << std::endl;

    std::cout << "Media: "
              << media
              << std::endl;

    int primoNumero = 12;
    int secondoNumero = 8;

    int risultatoSomma =
        somma(primoNumero, secondoNumero);

    int risultatoSottrazione =
        sottrai(primoNumero, secondoNumero);

    int risultatoMoltiplicazione =
        moltiplica(primoNumero, secondoNumero);

    std::cout << "Somma: "
              << risultatoSomma
              << std::endl;

    std::cout << "Sottrazione: "
              << risultatoSottrazione
              << std::endl;

    std::cout << "Moltiplicazione: "
              << risultatoMoltiplicazione
              << std::endl;

    char utente[50] = "Marco";

    if (strlen(utente) > 3)
    {
        std::cout << "Utente valido"
                  << std::endl;
    }
    else
    {
        std::cout << "Utente non valido"
                  << std::endl;
    }

    int indice = 0;

    while (indice < 4)
    {
        std::cout << "Passo "
                  << indice
                  << std::endl;

        indice++;
    }

    int totale = 0;

    for (int i = 0; i < DIMENSIONE; i++)
    {
        totale += numeri[i];
    }

    std::cout << "Totale elementi: "
              << totale
              << std::endl;

    bool trovato = false;

    for (int i = 0; i < DIMENSIONE; i++)
    {
        if (numeri[i] == 25)
        {
            trovato = true;
            break;
        }
    }

    if (trovato)
    {
        std::cout << "Valore presente"
                  << std::endl;
    }
    else
    {
        std::cout << "Valore assente"
                  << std::endl;
    }

    return 0;
}