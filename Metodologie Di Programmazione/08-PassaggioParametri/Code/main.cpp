/**
 * Esempio di codice su i tipi di passaggio di parametri:
 * - Passaggio per RIFERIMENTO
 * - Passaggio per VALORE
 */

#include <iostream>

/// Funzione con paramentri passati per valore
void sum(int, int, int);
/// Stessa funzione con paramentri passati per riferimento
void sum(int&, int&, int&);


/// Funzione con paramentri passati per valore
void swap(int, int);
/// Stessa funzione con paramentri passati per riferimento
void swap2(int&, int&);

// Codici ANSI per i colori
const std::string RESET = "\033[0m";  // Resetta il colore
const std::string RED = "\033[31m";  // Rosso
const std::string GREEN = "\033[32m";  // Verde
const std::string YELLOW = "\033[33m";  // Giallo
const std::string BLUE = "\033[34m";  // Blu
const std::string MAGENTA = "\033[35m";  // Magenta
const std::string CYAN = "\033[36m";  // Ciano

int main() {

    int a = 34, b = 22, c = 0;
    int d = 27, e = 18, f = 0;

    std::cout << "Entità prima dello scambio" << std::endl;
    std::cout << "A:" << a << ", B:" << b << std::endl;
    swap(a, b);
    std::cout << "Entità dopo dello scambio" << std::endl;
    std::cout << "A:" << a << ", B:" << b << std::endl;

    std::cout << std::endl;

    std::cout << "Entità prima dello scambio" << std::endl;
    std::cout << "A:" << a << ", B:" << b << std::endl;
    swap2(a, b);
    std::cout << "Entità dopo dello scambio" << std::endl;
    std::cout << "A:" << a << ", B:" << b << std::endl;

    return 0;
}


/**
 * In questa funzione andiamo ad inserire nella variabile LOCALE s
 * la somma di l e r, e questa non va a modificare la variabile definita
 * nello scope della funzione main perché non è stata passata per riferimento
 *
 * @param l PASSATO PER VALORE
 * @param r PASSATO PER VALORE
 * @param s PASSATO PER VALORE
 */
void sum(int l, int r, int s) {
    s = r + l;
}

/**
 * Al contrario della funzione definita sopra, questa funzione modifica effettivamente
 * la variabile s, essendo passata per RIFERIMENTO
 *
 * @param l PASSATO PER RIFERIMENTO
 * @param r PASSATO PER RIFERIMENTO
 * @param s PASSATO PER RIFERIMENTO
 */
void sum(int& l, int& r, int& s) {
    s = l + r;
}

/**
 * Funzione di scambio:
 * in questo caso non avviene alcuno scambio perche i parametri vengono passati per valore
 * e quindi non vengono modificate le entità passate
 *
 * @param l PASSATO PER VALORE
 * @param r PASSATO PER VALORE
 */
void swap(int l, int r) {
    std::cout << BLUE << "chiamato swap() con parametri passati per valore" << RESET << std::endl;
    int tmp = l;
    l = r;
    r = tmp;
}

/**
 * Funzione di scambio:
 * Invece in questo caso AVVIENE lo scambio perche i parametri vengono passati per riferimento
 * permettendo così la modifica delle entià
 *
 * @param l PASSATO PER RIFERIMENTO
 * @param r PASSATO PER RIFERIMENTO
 */
void swap2(int& l, int& r) {
    std::cout << BLUE << "chiamato swap() con parametri passati per riferimento" << RESET << std::endl;
    int tmp = l;
    l = r;
    r = tmp;
}