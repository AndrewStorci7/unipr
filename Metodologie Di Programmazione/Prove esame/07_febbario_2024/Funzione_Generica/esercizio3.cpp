#include <iostream>
#include <vector>
#include "min_elem.h"

int main() {

    using namespace Esercizio3;
    std::vector<int>         vi = {2, 6, 1, 8, 5, 3, 9, 7, 3, 2, -3, 7, 4};
    std::vector<double>      vd = {2.098, 2.987, 2.1162, 2.3374, 2.198321, 2.3094, 1.987};
    std::vector<std::string> vs = {};
    std::vector<const char*> vc = {"prova", "ciao", "salamaleku"};

    print(vi.begin(), vi.end());
    auto check_i = min_element(vi.begin(), vi.end(), LowerThan<int>{});
    std::cout << *check_i << std::endl;

    print(vd.begin(), vd.end());
    auto check_d = min_element(vd.begin(), vd.end(), LowerThan<double>{});
    std::cout << *check_d << std::endl;

    print(vc.begin(), vc.end());
    auto check_s = min_element(vc.begin(), vc.end(), LowerThan<const char*>{});
    std::cout << *check_s << std::endl;

    // print(vs.begin(), vs.end());
    // auto check_s = min_element(vs.begin(), vs.end(), LowerThan<std::string>{});
    // std::cout << *check_s << std::endl;
}