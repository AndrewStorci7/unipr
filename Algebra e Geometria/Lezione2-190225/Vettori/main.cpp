#include <iostream>
#include <map>
#include "common/start/start.h"

int main() {

    using START_AEG::map_v;

    map_v v_vettori;

    START_AEG::start(std::move(v_vettori));

    // Used for Vettori_test
    // Lezione2_Vettori::Vettore<int> prova;
    // std::cin >> prova;
    // const auto copia = prova;
    // std::cout << prova << std::endl;
    // std::cout << prova.to_string() << std::endl;

    return 0; // end of the program, bye bye, salamaleku
}
