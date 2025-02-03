#include <iostream>
#include <memory>
#include "console.h"

int main() {
    
/// Unique Pointer
    std::unique_ptr<int> ui(new int(45));
    // std::unique_ptr<int> uii = new int(54); // Errore

    // prova = ui; // Errore a compile-time: un unique pointer non può essere copiato
    auto prova = std::move(ui);
    std::cout << "[" << YELLOW << "typeof 'ui': " << typeid(ui).name() << RESET << "]" << std::endl;
    std::cout << "[" << YELLOW << "typeof 'prova': " << typeid(prova).name() << RESET << "]" << std::endl;
    std::cout << "*prova[" << prova.get() << "]: " << *prova << std::endl;
    // std::cout << "*ui[" << ui.get() << "]: " << *ui << std::endl;
    // std::cout << "*ui: " << *ui << std::endl;
    // ++(*ui); // Errore: non è possibile incrementare perché ui viene invalidato essendo che è statao spostato in una nuova zona di memoria
    ++(*prova); // Legale

    std::cout << "*prova (dopo incremento)[" << prova.get() << "]: " << *prova << std::endl;
    // std::cout << "*ui (dopo incremento): " << *ui << std::endl; // Errore UB: core dump 

    std::cout << std::endl;

/// Shared Pointer
    std::shared_ptr<int> si(new int(22));
    std::shared_ptr<int> sii;

    sii = si;

    std::cout << "*si: " << si.get() << std::endl;
    std::cout << "*sii: " << sii.get() << std::endl;

    {
        std::shared_ptr<int> siii;
        siii = sii;
        std::cout << "*siii: " << siii.get() << std::endl;
        std::cout << "[" << GREEN << "Incremento siii" << RESET << "]" << std::endl;
        ++(*siii);
        std::cout << "*siii (dopo incremento)[" << siii.get() << "]: " << *siii << std::endl;
        std::cout << "*sii (dopo incremento)[" << sii.get() << "]: " << *sii << std::endl;
        std::cout << "*si (dopo incremento)[" << si.get() << "]: " << *si << std::endl;
    }

    std::cout << "[" << RED << "Elimino siii uscendo dallo scope locale" << RESET << "]" << std::endl;
    ++(*si);
    std::cout << "[" << GREEN << "Incremento si" << RESET << "]" << std::endl;
    std::cout << "*si (dopo incremento)[" << si.get() << "]: " << *si << std::endl;
    std::cout << "*sii (dopo incremento)[" << sii.get() << "]: " << *sii << std::endl;

    std::cout << std::endl;

/// Weak Pointer
    // std::weak_ptr<int> wi(new int(76)); // Errore: non può essere inizializzato con un raw pointer
    std::weak_ptr<int> wi; // Legittimo, perché un weak pointer gestisce un puntatore condiviso senza partecipare all gestione della memoria
    {
        std::shared_ptr<int> salamaleku(new int(4));
        wi = salamaleku;

        std::cout << "*salamaleku: " << *salamaleku << std::endl;
        std::cout << "*wi: " << wi.lock() << std::endl;

        std::cout << "[" << GREEN << "Incremento salamaleku" << RESET << "]" << std::endl;
        ++(*salamaleku);
        std::cout << "*salamaleku: " << *salamaleku << std::endl;
        std::cout << "*wi: " << wi.lock() << std::endl;
    }

    std::cout << "[" << RED << "Elimino salamaleku uscendo dallo scope locale" << RESET << "]" << std::endl;
    std::cout << "*wi: " << wi.lock() << std::endl;
}