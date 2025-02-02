#include <iostream>
#include <iterator>
#include <vector>
#include <forward_list>

#include "console.h"

template <typename Iter>
void advance_helper(Iter it, int n, std::random_access_iterator_tag) {
    std::cout << YELLOW << "called advance_helper() for 'Random Access Iterator TAG'" << RESET << std::endl;
    it += n;
}

template <typename Iter>
void advance_helper(Iter it, int n, std::forward_iterator_tag) {
    std::cout << YELLOW << "called advance_helper() for 'Forward Iterator TAG'" << RESET << std::endl;
    for ( int i = 0; i < n; ++i ) {
        ++it; 
    }
}

template <typename Iter>
void advance(Iter it, int n) {
    advance_helper(it, n, typename std::iterator_traits<Iter>::iterator_category{});
}

int main() {

    std::vector<int> vd = {1, 4, 2, 8, 7};
    std::forward_list<int> fw = {2, 5, 7, 1, 8, 5};
    auto it_vd = vd.begin();
    auto it_fw = fw.begin();

    std::cout << MAGENTA << "[vector<int> size] " << RESET << vd.size() << std::endl;
    std::cout << CYAN << "[forward_list<int> size] " << RESET << distance(fw.begin(), fw.end()) << std::endl;

    advance(it_vd, 3);
    advance(it_fw, 2);

    std::cout << MAGENTA << "[vector<int> new size] " << RESET << vd.size() << std::endl;
    std::cout << CYAN << "[forward_list<int> new size] " << RESET << distance(fw.begin(), fw.end()) << std::endl;

}