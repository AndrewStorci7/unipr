#include <iostream>
#include <string>

namespace N {
    struct C {
        std::string& first() { std::string ret = "DAAA"; std::cout << "Funzione #1" << std::endl; return ret; } // funzione #1
        const std::string& first() const { std::string ret = "DAAA"; std::cout << "Funzione #2" << std::endl; return ret; } // funzione #2
        std::string& last() { std::string ret = "DAAA"; std::cout << "Funzione #3" << std::endl; return ret; } // funzione #3
        const std::string& last() const { std::string ret = "DAAA"; std::cout << "Funzione #4" << std::endl; return ret; } // funzione #4
    }; // class C

    void bar(double) { std::cout << "Funzione #5" << std::endl; } // funzione #5
    std::string& bar(int) { std::string ret = "DAAA"; std::cout << "Funzione #6" << std::endl; return ret; } // funzione #6
} // namespace N

void foo(N::C& cm, const N::C& cc) {
    std::string& s1 = cm.first(); // chiamata A
    const std::string& s2 = cm.last(); // chiamata B
    // std::string& s3 = cc.first(); // chiamata C
    const std::string& s4 = cc.last(); // chiamata D
    // bar(s4.size()); // chiamata E
}

int main() {
    N::C cm;
    const N::C& cc = cm;
    foo(cm, cc);
    return 0;
}
