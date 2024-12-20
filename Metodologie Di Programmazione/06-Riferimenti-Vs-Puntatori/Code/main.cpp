/**
 * Lezione 02/10/2024 - Puntatori vs Riferimenti
 * In questo codice vi sono delle applicazioni delel regole dei riferimenti e dei puntatori
 *
 * @author Andrea Storci aka dreean
 */

#include "console.h"
#include <iostream>

int main() {
    enableANSI();

    /**
     * I puntatori sono oggetti e possono essere nulli.
     * Per definiire un puntatore nullo si utilizza la sintassi:
     * tipo_puntatore* nome = nullptr
     */
    int* p; // dichiarazione di puntatore
    int* p_null = nullptr;  // dichiarazioen e definizione di un puntatore
                            // che punta a nullptr

    std::cout << "Puntatore non definito: \n\t" << GREEN << "Indirizzo di memoria: " << RESET << p << BLUE << "\n\tValore assegnato (casuale): " << RESET << (*p) << std::endl << std::endl;
    std::cout << "Puntatore definito con nullptr: \n\t" << GREEN << "Indirizzo di memoria: " << RESET << p_null << BLUE << "\n\tValore assegnato: " << RESET << RED << "Errore: un puntatore nullptr non ha valore" << RESET << std::endl << std::endl;

    int i = 10;
    p_null = &i;
    int& r = i;
    // int& r_error; // ERRORE: un riferimento non può essere nullo
    bool sonoUguali = p_null == &i;
    bool sonoUguali2 = &r == &i;
    bool sonoUguali3 = p == p_null;

    std::cout << "Riferimento di i (&i) e il suo valore: \n\t" << GREEN << "Indirizzo di memoria: " << RESET << &i << BLUE << "\n\tValore assegnato: " << RESET << i << std::endl << std::endl;
    std::cout << "Puntatore definito con nullptr: \n\t" << GREEN << "Indirizzo di memoria: " << RESET << p_null << BLUE << "\n\tValore assegnato: " << RESET << (*p_null) << std::endl << std::endl;
    std::cout << "Riferimento di r : \n\t" << GREEN << "Indirizzo di memoria: " << RESET << &r << BLUE << "\n\tValore assegnato: " << RESET << r << std::endl << std::endl;

    std::cout << "Prova del nove: \n\t" << "L'indirizzo di memoria di " << BLUE << "p_null(" << p_null << ")" << RESET << " e' uguale all'indirizzo di memoria di " << BLUE << "i(" << &i << ") "<< RESET << "?" << std::endl;
    std::cout << "\t" << sonoUguali << " = " << ((sonoUguali) ? "Vero" : "Falso") << std::endl;

    std::cout << "\n\t" << "L'indirizzo di memoria di " << BLUE << "r(" << &r << ")" << RESET << " e' uguale all'indirizzo di memoria di " << BLUE << "i(" << &i << ") "<< RESET << "?" << std::endl;
    std::cout << "\t" << sonoUguali2 << " = " << ((sonoUguali2) ? "Vero" : "Falso") << std::endl;

    std::cout << "\n\t" << "L'indirizzo di memoria di " << BLUE << "p(" << p << ")" << RESET << " e' uguale all'indirizzo di memoria di " << BLUE << "p_null(" << p_null << ") "<< RESET << "?" << std::endl;
    std::cout << "\t" << sonoUguali3 << " = " << ((sonoUguali3) ? "Vero" : "Falso") << std::endl;

    int prova = 123412;
    const int prova2 = 88272;
    int& r_prova = prova;

    const int* cp = &prova;
    const int* cr_p = &r_prova;
    int* const pc = &prova;
    const int* const ccr_p = &r_prova;

    std::cout << "\nPuntatore con oggetto puntato costante (const int*): \n\t" << GREEN << "Indirizzo di memoria: " << RESET << cp << BLUE << "\n\tValore assegnato: " << RESET << (*cp) << std::endl << std::endl;
    std::cout << "\nPuntatore con oggetto puntato costante a riferimento (const int*): \n\t" << GREEN << "Indirizzo di memoria: " << RESET << cr_p << BLUE << "\n\tValore assegnato: " << RESET << (*cr_p) << std::endl << std::endl;
    std::cout << "\nPuntatore costante (int* const): \n\t" << GREEN << "Indirizzo di memoria: " << RESET << pc << BLUE << "\n\tValore assegnato: " << RESET << (*pc) << std::endl << std::endl;

    std::cout << MAGENTA << "Valore della variabile " << RESET << CYAN << "prova" << RESET << MAGENTA << " PRIMA dell'assegnamento del puntatore pc" << RESET << std::endl << prova << std::endl;

    // pc = &prova2;    // ERRORE: non posso modificare un puntatore definito const
    *pc = prova2;       // Legale: l'oggetto puntato è modificabile

    std::cout << "Puntatore costante (int* const): \n\t" << GREEN << "Indirizzo di memoria: " << RESET << pc << BLUE << "\n\tValore assegnato: " << RESET << (*pc) << std::endl << std::endl;
    std::cout << MAGENTA << "Valore della variabile " << RESET << CYAN << "prova" << RESET << MAGENTA << " DOPO dell'assegnamento del puntatore pc" << RESET << std::endl << prova << std::endl;

    // ccr_p;

    return 0;
}
