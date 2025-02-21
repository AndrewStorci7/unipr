#include "start.h"
#include "console/console.h"

namespace START_AEG {

    std::string last_output;   // contains last output
    std::string h_last_output = CCC::mkf_italic(CCC::mkf_bold("[\t\t\tLast Output\t\t\t]"));
    std::string actual_size;   // contains the actual size of the map of vectors
    std::string choise;        // contains the choise of the user based on choises from menu
    bool exit = false;         // default value: false

    void start(map_v&& vet) {
        // visual menu
        do {
            // update the actual_dimension variable
            actual_size = CCC::mkf_bold("[dimensione attuale: " + std::to_string(vet.size()) + "].");
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
            std::cout << "6. Prodotto vettoriale tra due vettori." << std::endl;
            std::cout << "7. Stampa tutti i vettori esistenti." << std::endl;
            CCC::reset_terminal_color(); // reset color

            CCC::print_colorized("green"); // set color for terminal
            std::cout << CCC::mkf_italic("Quale operazione vuoi eseguire ? ");
            CCC::reset_terminal_color(); // reset color

            std::getline(std::cin, choise);

            if (choise == "salamaleku") exit = !exit;
            else menu(choise, vet, std::move(last_output));

        } while (!exit);

        std::cout << "Bye Bye, Salamaleku!" << std::endl;
    }

    void menu(const std::string& choise, map_v& vet, std::string&& last_output) {
        switch (std::stoi(choise)) {
            case 1: {
                /// Aggiunge un nuovo vettore all'interno di vet {map<std::string, Vettore<int>>}
                menu_add(vet, std::move(last_output));
                break;
            }
            case 2: {
                // TODO:
                // remove vector
                break;
            }
            case 3: {
                /// Somma due vettori
                menu_sum(vet, std::move(last_output));
                break;
            }
            case 4: {
                // TODO:
                // substract 2 vectors
                break;
            }
            case 5: {
                /// Prodotto scalare di due vettori
                menu_pscalar(vet, std::move(last_output));
                break;
            }
            case 6: {
                // TODO:
                // vectorial product of 2 vectors
                break;
            }
            case 7: {
                /// Stampa tutti i vettori inseriti
                menu_print(vet, std::move(last_output));
                break;
            }
            default:
                break;
        }
    }

    /**
     *
     * @param vet
     * @param last_output
     */
    void menu_sum(map_v& vet, std::string&& last_output) {
        std::string tmp, output;
        std::cout << "Inserisci i nomi dei vettori che vuoi utilizzare;" <<
            CCC::mkf_bold(CCC::mkf_italic("\n!Attenzione! per questione salamalekuniane verrano presi in considerazione solamente i primi due indici inseriti")) <<
            "\n[separati da una virgola; ad es: v, w]: ";

        std::getline(std::cin, tmp);
        auto splitted = CF_AEG::split<std::string>(tmp);

        const Vettore<int> ret_addition = vet[splitted.at(0)] + vet[splitted.at(1)];

        output = "Risultato ottenuto: " + ret_addition.to_string();
        last_output = output;

        std::cout << output << std::endl;
    }

    /**
     *
     * @param vet
     * @param last_output
     */
    void menu_add(map_v& vet, std::string&& last_output) {
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
            vet[index_vector] = v;
        } catch (const std::exception& e) {
            std::cerr << "\nError occured on Lezione2_Vettori::scan()" << e.what() << std::endl;
            vet.erase(index_vector);
        } catch (...) {
            std::cerr << "\nError occurred while getting the vector from keyboard" << std::endl;
            vet.erase(index_vector);
        }
    }

    /**
     *
     * @param vet
     * @param last_output
     */
    void menu_pscalar(map_v& vet, std::string&& last_output) {

        last_output = "Prodotto scalare calcolato: ";
        std::string str;
        std::cout << "Scegli due vettori \n";
        std::cout << print_keyvalues_only(vet) << "\n>> ";
        while (str.empty()) {
            std::cout << "Inserisci il nome dei vettori: ";
            std::getline(std::cin, str);
            if (std::cin.fail())
                CF_AEG::clear_cin_buffer();
        }

        auto keys = CF_AEG::split<std::string>(str);
        // prendo solamente i primi due vettori (non credo nemmeno esisti il prodotto scalare di piu' di due vettori)
        try {
            auto result = CCC::mkf_bold(std::to_string(Lezione2_Vettori::scalar_product(
                vet[keys[0]],
                vet[keys[1]]
            )));
            last_output += CCC::mk_colorized(result);
        } catch (const std::runtime_error& e) {
            std::cerr << std::endl << e.what() << std::endl;
        } catch (...) {
            std::cerr << std::endl << "Unknown error caught during product scalar" << std::endl;
        }
    }

    /**
     * Print a map composed by every vector added during the program
     * @param vet
     * @param last_output
     */
    void menu_print(const map_v& vet, std::string&& last_output) {
        last_output.clear(); // clearing last_output
        for ( auto it = vet.begin(); it != vet.end(); ++it )
            last_output += it->first + " = { " + it->second.to_string() + " };\n";
    }

    /**
     *
     * @param vet
     */
    std::string print_keyvalues_only(const map_v& vet) {
        std::string ret = "[ ";
        for ( auto it = vet.begin(); it != vet.end(); ++it ) {
            ret += it->first;
            if (std::next(it) != vet.end())
                ret += ", ";
        }
        ret += " ]";

        return ret;
    }

} // START_AEG