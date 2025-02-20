#include "start.h"
#include "console/console.h"

namespace START_AEG {

    void start(map_v&& vet) {
        // string taht store the user choise
        std::string str;
        bool exit = false;

        // visual menu
        do {
            CF_AEG::clear_console(); // clear console for security reasons

            CCC::print_colorized(); // set color for terminal
            std::cout << "1. Aggiungi un nuovo vettore [dimensione attuale: " << vet.size() << "]." << std::endl;
            std::cout << "2. Rimuovi un vettore." << std::endl;
            std::cout << "3. Somma tra due vettori." << std::endl;
            std::cout << "4. Sottrazione tra due vettori." << std::endl;
            std::cout << "5. Prodotto scalare tra due vettori." << std::endl;
            std::cout << "6. Prodotto vettoriale tra due vettori." << std::endl;
            std::cout << "7. Stampa tutti i vettori esistenti." << std::endl;
            CCC::reset_terminal_color(); // reset color

            CCC::print_colorized("green"); // set color for terminal
            CCC::italic_font("Quale operazione vuoi eseguire ? ");
            CCC::reset_terminal_color(); // reset color

            std::getline(std::cin, str);

            if (str == "salamaleku") exit = !exit;
            else menu(str, vet);

        } while (!exit);

        std::cout << "Bye Bye, Salamaleku!" << std::endl;
    }

    void menu(const std::string& choise, map_v& vet) {
        switch (std::stoi(choise)) {
            case 1: {
                /// Aggiunge un nuovo vettore all'interno di vet {map<std::string, Vettore<int>>}
                menu_add(vet);
                break;
            }
            case 2: {
                // TODO:
                // remove vector
                break;
            }
            case 3: {
                /// Somma due vettori
                menu_sum(vet);
                break;
            }
            case 4: {
                // TODO:
                // substract 2 vectors
                break;
            }
            case 5: {
                // TODO:
                // scalar product of 2 vectors
                break;
            }
            case 6: {
                // TODO:
                // vectorial product of 2 vectors
                break;
            }
            case 7: {
                // TODO:
                // print very vector inside `vet`
                menu_print(vet);
                break;
            }
            default:
                break;
        }
    }

    void menu_add(map_v& vet) {
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

    void menu_sum(map_v& vet) {
        std::string tmp;
        std::cout << "Inserisci i nomi dei vettori che vuoi utilizzare;" <<
            "\n!Attenzione! per questione salamalekuniane verrano presi in considerazione solamente i primi due indici inseriti" <<
            "\n[separati da una virgola; ad es: v, w]: ";

        std::getline(std::cin, tmp);
        auto splitted = CF_AEG::split<std::string>(tmp);

        const Vettore<int> ret_addition = vet[splitted.at(0)] + vet[splitted.at(1)];

        std::cout << "Risultato ottenuto: " << ret_addition << std::endl;
    }

    void menu_print(const map_v& vet) {
        for ( auto it = vet.begin(); it != vet.end(); ++it )
            std::cout << it->first << " = { " << it->second << " };" << std::endl;
    }

} // START_AEG