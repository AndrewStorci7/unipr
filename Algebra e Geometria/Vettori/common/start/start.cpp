#include "start.h"
#include "console/console.h"

namespace START_AEG {

    std::string last_output;   // contains last output
    std::string h_last_output = CCC::mkf_italic(CCC::mkf_bold("[\t\t\tLast Output\t\t\t]"));
    std::string actual_size;   // contains the actual size of the map of vectors
    std::string choise;        // contains the choise of the user based on choises from menu
    bool exit = false;         // default value: false

    /**
     * Scan from keyboard
     * @param str
     * @param map
     */
    void scan(std::string& str, const map_v& map, const std::string& option) {
        std::cout << ((option == "mult") ? "Scegli un vettore \n" : "Scegli due vettori \n");
        std::cout << print_keyvalues_only(map) << std::endl;
        while (str.empty()) {
            std::cout << ">> ";
            std::getline(std::cin, str);
            if (std::cin.fail())
                CF_AEG::clear_cin_buffer();
        }
    }

    /**
     * Scan from keyboard
     * @param value
     * @param map
     * @param option
     */
    void scan(int& value, const map_v& map, const std::string& option) {
        std::cout << ((option == "mult") ? "Moltiplicatore \n" : "Salamaleku \n");
        std::cout << print_keyvalues_only(map) << std::endl;
        while (value == 0) {
            std::cout << ">> ";
            std::cin >> value;
            if (std::cin.fail())
                CF_AEG::clear_cin_buffer();
        }
    }

    void start(map_v&& map) {
        // visual menu
        do {
            // update the actual_dimension variable
            actual_size = CCC::mkf_bold("[dimensione attuale: " + std::to_string(map.size()) + "].");
            CCC::mk_colorized(std::move(h_last_output), "magenta");

            CCC::clear_console(); // clear console for security reasons

            // print last output from `last_output`
            if (!last_output.empty())
                std::cout << h_last_output << std::endl << last_output << std::endl << std::endl;

            CCC::print_colorized(); // set color for terminal
            std::cout << "1. Aggiungi un nuovo vettore ";
            std::cout << actual_size << std::endl;
            CCC::print_colorized(); // set color for terminal
            std::cout << "2. Rimuovi un vettore." << std::endl;
            std::cout << "3. Somma tra due vettori." << std::endl;
            std::cout << "4. Sottrazione tra due vettori." << std::endl;
            std::cout << "5. Prodotto scalare tra due vettori." << std::endl;
            std::cout << "6. Norma di un vettore." << std::endl;
            std::cout << "7. Prodotto vettoriale tra due vettori." << std::endl;
            std::cout << "8. Moltiplica un vettore per una costante." << std::endl;
            std::cout << "9. Stampa tutti i vettori esistenti." << std::endl;
            CCC::reset_terminal_color(); // reset color

            CCC::print_colorized("green"); // set color for terminal
            std::cout << CCC::mkf_italic("Quale operazione vuoi eseguire ? ");
            CCC::reset_terminal_color(); // reset color

            std::getline(std::cin, choise);

            if (choise == "salamaleku") exit = !exit;
            else menu(choise, map, std::move(last_output));

        } while (!exit);

        std::cout << "Bye Bye, Salamaleku!" << std::endl;
    }

    void menu(const std::string& choise, map_v& map, std::string&& last_output) {
        try {
            const int choise_int = std::stoi(choise);
            switch (choise_int) {
                case 1: {
                    /// Aggiunge un nuovo vettore all'interno di map {map<std::string, Vettore<int>>}
                    menu_add(map, std::move(last_output));
                    break;
                }
                case 2: {
                    // TODO:
                    // remove vector
                    break;
                }
                case 3: {
                    /// Somma due vettori
                    menu_sum(map, std::move(last_output));
                    break;
                }
                case 4: {
                    // TODO:
                    // substract 2 vectors
                    break;
                }
                case 5: {
                    /// Prodotto scalare di due vettori
                    menu_pscalar(map, std::move(last_output));
                    break;
                }
                case 6: {
                    /// Norma di un vettore
                    menu_norma(map, std::move(last_output));
                    break;
                }
                case 7: {
                    // TODO:
                    // vectorial product of 2 vectors
                    menu_pvectorial(map, std::move(last_output));
                    break;
                }
                case 8: {
                    /// Moltiplica un vettore per un numero
                    menu_multiply(map, std::move(last_output));
                    break;
                }
                case 9: {
                    /// Stampa tutti i vettori inseriti
                    menu_print(map, std::move(last_output));
                    break;
                }
                default:
                    break;
            }
        } catch (const std::invalid_argument& e) {
            std::cerr << "Errore: " << e.what() << std::endl;
        }
    }

    /**
     *
     * @param map
     * @param last_output
     */
    void menu_sum(map_v& map, std::string&& last_output) {
        std::string tmp, output;
        std::cout << "Inserisci i nomi dei vettori che vuoi utilizzare;" <<
            CCC::mkf_bold(CCC::mkf_italic("\n!Attenzione! per questione salamalekuniane verrano presi in considerazione solamente i primi due indici inseriti")) <<
            "\n[separati da una virgola; ad es: v, w]: ";

        std::getline(std::cin, tmp);
        auto splitted = CF_AEG::split<std::string>(tmp);

        const Vettore<int> ret_addition = map[splitted.at(0)] + map[splitted.at(1)];

        output = "Risultato ottenuto: " + ret_addition.to_string();
        last_output = output;

        std::cout << output << std::endl;
    }

    /**
     *
     * @param map
     * @param last_output
     */
    void menu_add(map_v& map, std::string&& last_output) {
        // temporary variable that store the name of the index
        std::string index_vector;
        try {
            while (index_vector.empty()) {
                std::cout << "Inserisci il nome del vettore: ";
                std::cin >> index_vector;
                if (std::cin.fail()) {
                    CF_AEG::clear_cin_buffer();
                    index_vector = "";
                }
            }

            // validando il fatto che `index_vector` non sia vuoto
            assert(!index_vector.empty());

            Vettore<int> v;
            std::cin >> v;
            map[index_vector] = v;
        } catch (const std::exception& e) {
            std::cerr << "\nError occured on Lezione2_Vettori::scan()" << e.what() << std::endl;
            map.erase(index_vector);
        } catch (...) {
            std::cerr << "\nError occurred while getting the vector from keyboard" << std::endl;
            map.erase(index_vector);
        }
    }

    /**
     *
     * @param map
     * @param last_output
     */
    void menu_pscalar(map_v& map, std::string&& last_output) {
        last_output = "Prodotto scalare calcolato: ";
        std::string str;
        scan(str, map);

        auto keys = CF_AEG::split<std::string>(str);

        // prendo solamente i primi due vettori (non credo nemmeno esisti il prodotto scalare di piu' di due vettori)
        try {
            // check if teh vector selected exists
            if (!CF_AEG::check_if_exists(map, keys)) {
                last_output = "I vettori selezionati non esistono";
                return;
            }

            assert(typeid(map[keys[0]]).name() != "N16Lezione2_Vettori7VettoreIiEE");

            auto result = scalar_product(
                map[keys[0]],
                map[keys[1]]
            );
            auto result_str = CCC::mkf_bold(std::to_string(result));
            last_output += CCC::mk_colorized(result_str);

            // check if they
            assert(map[keys[0]].size() != 0 and map[keys[1]].size() != 0);
        } catch (const std::runtime_error& e) {
            std::string tmp_error = "Error: " + std::string(e.what());
            last_output = CCC::mk_colorized(tmp_error, "red");
        } catch (...) {
            std::string tmp_error = "Unknown error caught during product scalar";
            last_output = CCC::mk_colorized(tmp_error, "red");
        }
    }

    /**
     * Handle norma
     * @param map
     * @param last_output
     */
    void menu_norma(map_v& map, std::string&& last_output) {
        std::string str;
        scan(str, map);

        last_output = "Norma calcolata: ";
        auto keys = CF_AEG::split<std::string>(str);

        try {
            // check if teh vector selected exists
            if (!CF_AEG::check_if_exists(map, keys)) {
                last_output = "I vettori selezionati non esistono";
                return;
            }

            // For the norma I will take only the first key
            auto result = norma(map[keys[0]]);

            if (result == -1)
                last_output += "operazione eseguita su un vettore nullo (" + CCC::mkf_bold(std::to_string(static_cast<int>(result))) + ")";
            else {
                std::string string_bold = CCC::mkf_bold(std::to_string(result));
                last_output += CCC::mk_colorized(string_bold);
            }
        } catch (const std::runtime_error& e) {
            std::string tmp_error = "Error: " + std::string(e.what());
            last_output = CCC::mk_colorized(tmp_error, "red");
        } catch (...) {
            std::string tmp_error = "Unknown error caught during product scalar";
            last_output = CCC::mk_colorized(tmp_error, "red");
        }
    }

    /**
     * Handle vectorial product
     * @param vet
     * @param last_output
     */
    void menu_pvectorial(map_v& map, std::string&& last_output) {
        std::string str;
        scan(str, map);

        last_output = "Prodotto vettoriale calcolato: ";
        auto keys = CF_AEG::split<std::string>(str);

        try {
            // check if teh vector selected exists
            if (!CF_AEG::check_if_exists(map, keys)) {
                last_output = "I vettori selezionati non esistono";
                return;
            }

            auto result = vectorial_product(
                map[keys[0]],
                map[keys[1]]
            );

            std::string string_bold = CCC::mkf_bold(result.to_string());
            last_output += CCC::mk_colorized(string_bold);
        } catch (const std::runtime_error& e) {
            std::string tmp_error = "Error: " + std::string(e.what());
            last_output = CCC::mk_colorized(tmp_error, "red");
        } catch (...) {
            std::string tmp_error = "Unknown error caught during product scalar";
            last_output = CCC::mk_colorized(tmp_error, "red");
        }
    }

    /**
     * Print a map composed by every vector added during the program
     * @param map
     * @param last_output
     */
    void menu_print(const map_v& map, std::string&& last_output) {
        last_output.clear(); // clearing last_output
        for ( const auto &it : map )
            last_output += it.first + " = { " + it.second.to_string() + " };\n";
    }

    /**
     * Handle multiplication with an integer
     * @param map
     * @param last_output
     */
    void menu_multiply(map_v& map, std::string&& last_output) {
        // last_output.clear();
        // std::string str;
        int value = 0;
        scan(value, map, "mult");

        // last_output =

    }

    /**
     *
     * @param map
     */
    std::string print_keyvalues_only(const map_v& map) {
        std::string ret = "[ ";
        for ( auto it = map.begin(); it != map.end(); ++it ) {
            ret += it->first;
            if (std::next(it) != map.end())
                ret += ", ";
        }
        ret += " ]";

        return ret;
    }

} // START_AEG