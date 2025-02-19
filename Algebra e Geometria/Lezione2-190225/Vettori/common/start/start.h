#ifndef VETTORE_AEG_START_H
#define VETTORE_AEG_START_H

#include <string>
#include <map>
#include <limits>
#include <cassert>

#include "vettore.h"

namespace START_AEG {

    using Lezione2_Vettori::Vettore;
    using map_v = std::map<std::string, Vettore<int>>;

    /**
     * Display the initial menu
     * @param vet {map_v&&}
     */
    void start(map_v&& vet);

    /**
     * Menu of the program
     * @param choise {const int&}
     * @param vet {map_v&}
     */
    void menu(const std::string& choise, map_v& vet);

    /**
     *
     * @param vet {}
     */
    void menu_sum(map_v& vet);

    /**
     *
     * @param vet {}
     */
    void menu_add(map_v& vet);

} // START_AEG

#endif //VETTORE_AEG_START_H
