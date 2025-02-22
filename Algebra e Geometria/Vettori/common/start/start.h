#ifndef VETTORE_AEG_START_H
#define VETTORE_AEG_START_H

#include <string>
#include <map>
#include "vettore.h"

namespace START_AEG {

    using Lezione2_Vettori::Vettore;
    using map_v = std::map<std::string, Vettore<int>>;

    // Variable with graphical purpose
    extern std::string last_output;   // contains last output
    extern std::string h_last_output; // header for last_output
    extern std::string actual_size;   // contains the actual size of the map of vectors
    extern std::string choise;        // contains the choise of the user based on choises from menu
    extern bool exit;                 // if set to true: exit, otherwise stay

    /**
     * Scan from keyboard
     * @param str
     * @param map
     */
    void scan(std::string& str, const map_v& map);

    /**
     * Display the initial menu
     * @param map
     */
    void start(map_v&& map);

    /**
     * Menu of the program
     * @param choise
     * @param map
     * @param last_output
     */
    void menu(const std::string& choise, map_v& map, std::string&& last_output);

    /**
     *
     * @param map
     * @param last_output
     */
    void menu_sum(map_v& map, std::string&& last_output);

    /**
     *
     * @param map
     * @param last_output
     */
    void menu_add(map_v& map, std::string&& last_output);

    /**
     *
     * @param map
     * @param last_output
     */
    void menu_pscalar(map_v& map, std::string&& last_output);

    /**
     *
     * @param map
     * @param last_output
     */
    void menu_norma(map_v& map, std::string&& last_output);

    /**
     * Handle vectorial product
     * @param map 
     * @param last_output 
     */
    void menu_pvectorial(map_v& map, std::string&& last_output);

    /**
     * Print a map composed by every vector added during the program
     * @param map
     * @param last_output
     */
    void menu_print(const map_v& map, std::string&& last_output);

    /**
     * Print only the key values of a map
     * @param map
     */
    std::string print_keyvalues_only(const map_v& map);

} // START_AEG

#endif //VETTORE_AEG_START_H
