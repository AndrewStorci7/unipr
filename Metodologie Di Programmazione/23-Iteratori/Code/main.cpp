#include <iostream>
#include <iterator>
#include <forward_list>
#include <list>
#include <vector>

#include "console.h"

int main() {

/*
// Input Iterator 
// Permettono solo lo spostamento in avanti
// 
// Esempio di utilizzo:
*/
    std::cout << RED << "[Input Iterator]" << RESET << std::endl;
    std::istream_iterator<double> i(std::cin);
    auto j = i;

    std::cout << *i << std::endl;
    std::cout << *j << std::endl;
    ++i;
    std::cout << *j << std::endl; // UB: undefined behavior

/*
// Forward Iterator
// Permettono di essere "riavvolti", ovvero, non vanno ad invalidare ulteriori iteratori 
// 
// Esempio di utilizzo:
*/
    std::cout << BLUE << "[Forward Iterator]" << RESET << std::endl;
    std::forward_list<int> fl = {4, 2, 8, 7, 9, 1, 2};

    // begin() ritorna un iteratore che permette la modifica
    for ( auto i = fl.begin(); i != fl.end(); ++i ) {
        std::cout << *i << "\t";
        *i += 10;
    }

    std::cout << std::endl;
    // cbegin() ritorna un iteratore costante
    for ( auto i = fl.cbegin(); i != fl.cend(); ++i )
        std::cout << *i << "\t";
    std::cout << std::endl;

/*
// Bidiretional Iterator
// Permettono di iterare una sequenza in tutte e due le direzioni 
// 
// Esempio di utilizzo:
*/
    std::cout << GREEN << "[Bidiretional Iterator]" << RESET << std::endl;
    std::list<int> l = {3, 8, 1, 9, 4, 7, 6};

    for ( auto i = l.begin(); i != l.end(); ++i ) {
        std::cout << *i << "\t";
        *i += 5;
    }

    std::cout << std::endl;
    for ( auto i = l.crend(); i != l.crbegin(); ) {
        --i; // Decrementare prima di dereferenziare, altrimenti overflow
        std::cout << *i << "\t";
    }    
    std::cout << std::endl;

    // std::cout << std::endl;
    for ( auto i = l.cend(); i != l.cbegin(); ) {
        --i; // Decrementare prima di dereferenziare, altrimenti overflow
        std::cout << *i << "\t";
    }
    std::cout << std::endl;

/*
// Random Access Iterator
// Permette l'accesso in una sequenza ad accesso casuale
// 
// Esempio di utilizzo:
*/
    std::cout << YELLOW << "[Random Access Iterator]" << RESET << std::endl;
    std::vector<std::string> vs = {"Ciao", "Marco", "Andrea", "Ludovico", "Marghe", "Salvo"};

    std::cout << vs.at(0) << std::endl;
    std::cout << vs[0] << std::endl;

/*
// Output Iterator
// Permette l'accesso in sola scritturaù
// 
// Esempio di utilizzo:
*/
    std::cout << MAGENTA << "[Output Iterator]" << RESET << std::endl;
    std::ostream_iterator<int> out(std::cout, "\n");

    for ( int i = 0; i < 10; ++i ) {
        *out = 10 * i;
        ++out;
    }
}   