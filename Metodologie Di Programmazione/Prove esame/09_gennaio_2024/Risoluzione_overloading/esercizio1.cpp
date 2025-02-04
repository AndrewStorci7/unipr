#include <iostream>
#include <string>

namespace N {    
    struct C {
        std::string& first() { std::string r = "#1"; return r; }; // funzione #1
        const std::string& first() const { std::string r = "#2"; return r; }; // funzione #2
        std::string& last() { std::string r = "#3"; return r; }; // funzione #3
        const std::string& last() const { std::string r = "#4"; return r; }; // funzione #4
    }; // class C

    void bar(double); // funzione #5
    std::string& bar(int); // funzione #6
} // namespace N

void foo(N::C& cm, const N::C& cc) {
    std::string& s1 = cm.first(); // chiamata A
    std::cout << s1 << std::endl;
    const std::string& s2 = cm.last(); // chiamata B
    std::cout << s2 << std::endl;
    std::string& s3 = cc.first(); // chiamata C
    std::cout << s3 << std::endl;
    const std::string& s4 = cc.last(); // chiamata D
    std::cout << s4 << std::endl;
    // bar(s4.size()); // chiamata E
}

int main() {

    N::C c;
    foo(c, c);
}