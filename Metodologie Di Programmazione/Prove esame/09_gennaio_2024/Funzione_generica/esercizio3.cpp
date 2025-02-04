#include <iostream>
#include <iterator>
#include <vector>
#include <list>
#include "console.h"

template <typename T, typename Iter>
void replace(Iter first, Iter last, const T& old_value, const T& new_value) {
    for ( ; first != last; ++first ) {
        if (*first == old_value)
            *first = new_value;
    }
}

template <typename Iter>
void print(Iter first, Iter last) {
    for ( ; first != last; ++first ) {
        std::cout << *first << "\t";
    }
    std::cout << std::endl;
}

int main() {

    std::vector<int> vi = {3, 5, 1, 7, 8, 5, 5, 5, 5, 5};
    std::vector<double> vii = {3.5, 5.2, 1.2, 7.4, 8.1, 5.6, 5.65, 5.78, 5.6, 5.6};
    std::list<int> li = {1, 5, 6, 2, 5, 3, 3, 3};
    std::list<const char*> lcc = {"prova", "salamaleku", "habib", "mandogay", "salam"};
    std::list<std::string> ls = {"salam", "maleku", "allah", "habib", "abdul"};

    std::cout << "[" << CYAN << "Sequenze prima della modifica" << RESET << "]" << std::endl; 
    print(vi.begin(), vi.end());
    print(vii.begin(), vii.end());
    print(li.begin(), li.end());
    print(lcc.begin(), lcc.end());
    print(ls.begin(), ls.end());
    replace(vi.begin(), vi.end(), 5, 9);
    replace(vii.begin(), vii.end(), 5.6, 0.0);
    replace(li.begin(), li.end(), 3, 1);
    replace(lcc.begin(), lcc.end(), static_cast<const char*>("prova"), static_cast<const char*>("ciao"));
    replace(ls.begin(), ls.end(), static_cast<std::string>("allah"), static_cast<std::string>("ciao"));

    std::cout << "[" << MAGENTA << "Sequenze dopo la chiamata a replace()" << RESET << "]" << std::endl;
    print(vi.begin(), vi.end());
    print(vii.begin(), vii.end());
    print(li.begin(), li.end());
    print(lcc.begin(), lcc.end());
    print(ls.begin(), ls.end());
}