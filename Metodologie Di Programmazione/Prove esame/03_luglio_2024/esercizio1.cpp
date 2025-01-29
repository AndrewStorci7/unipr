#include <iostream>

using namespace std;

namespace N {
    void foo(int, double) { cout << "funzione #1" << endl; } // funzione #1
    void foo(double, int) { cout << "funzione #2" << endl; } // funzione #2
} // namespace N

void foo(double, double) { cout << "funzione #3" << endl; } // funzione #3

int main() {
    foo(42, 3.14); // chiamata A
    N::foo(42, 3.14); // chiamata B
    using namespace N;
    foo(3.14, 42); // chiamata C
    using N::foo;
    foo(42, 3.14); // chiamata D
}