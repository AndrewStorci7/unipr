#include <iostream>
#include <map>
#include "common/start/start.h"
#include "matrici/matrice.h"

int main() {

    using START_AEG::map_v;
    using Lezione3_Matrici::Matrice;

    map_v v_vettori;

    // START_AEG::start(std::move(v_vettori));

    std::vector<int> v1 = { 1, 2, 3, 4, 5 };
    Lezione2_Vettori::Vettore<int> vet1 = v1;
    std::vector<int> v2 = { 1, 2, 3, 4, 5 };
    Lezione2_Vettori::Vettore<int> vet2 = v2;
    std::vector<int> v3 = { 1, 2, 3, 4, 5 };
    Lezione2_Vettori::Vettore<int> vet3 = v3;
    std::vector<int> v4 = { 1, 2, 3, 4, 5 };
    Lezione2_Vettori::Vettore<int> vet4 = v4;
    std::vector<Lezione2_Vettori::Vettore<int>> vect = { vet1, vet2, vet3, vet4 };
    Matrice<int> matrice = vect;

    auto prova = Lezione3_Matrici::gauss(matrice);

    /// Used for Vettori_test
    // Lezione2_Vettori::Vettore<int> prova;
    // std::cin >> prova;
    // const auto copia = prova;
    // std::cout << prova << std::endl;
    // std::cout << prova.to_string() << std::endl;

    /// Used for Vettori_test
    // std::vector<int> vv1 = { 1, 2, 3 };
    // std::vector<int> vv2 = { 5, 7, 2 };
    // Lezione2_Vettori::Vettore<int> v1 = vv1;
    // Lezione2_Vettori::Vettore<int> v2 = vv2;
    //
    // std::cout << "Typeof vv1: " << typeid(v1).name() << std::endl;
    // std::cout << "Typeof vv2: " << typeid(v2).name() << std::endl;
    //
    // Lezione2_Vettori::scalar_product(v1, v2);

    /// Used for Vettori_test
    // Lezione2_Vettori::Vettore<int> vettore;
    // std::cin >> vettore;
    // vettore.push(1); vettore.push(2); vettore.push(3);
    //
    // std::cout << vettore.size() << std::endl;
    // std::vector<int> vettore = { 0, 0, 0 };
    // Lezione2_Vettori::Vettore<int> nullo = vettore;
    // // Lezione2_Vettori::Vettore<int> nullo2 = { 0, 0, 0 };
    // std::cout << nullo;



    return 0; // end of the program, bye bye, salamaleku
}
