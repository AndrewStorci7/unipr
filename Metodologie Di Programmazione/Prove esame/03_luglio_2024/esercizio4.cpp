#include <iostream>
#include <stdexcept>
#include <vector>

int main() {
    std::vector<int> vi = {1, 2, 3, 4, 5, 6};
    
    try {
        std::cout << vi[3] << std::endl;    // stampa correttamente 4
        std::cout << vi.at(3) << std::endl; // stampa correttamente 4
        std::cout << vi.at(6) << std::endl; // l'eccezzione viene catturata dal blocco catch
    } 
    catch (std::out_of_range e) { 
        std::cerr << "Error: " << e.what() << std::endl;
    } 
    catch (...) {}
    
    std::cout << vi[6] << std::endl; // in questo caso stampera un valore casuale, perché stiamo accedendo una zona di memoria che va oltre la dimensione della sequenza  
    
    std::cout << vi.at(6) << std::endl; // in questo caso il programma termina con un errore
}