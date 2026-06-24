#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

/// apre il file CSV e carica le distanze in una matrice 2D dinamica, poi stampa un esempio di accesso alla matrice

// obiettivo: implementare kruskal e identificare gli ultimi archi aggiunti
// descrivere le coppie di città che corrispondono agli ultimi archi aggiunti e il significato geografico di queste coppie 

int main() {
    const char* filename = "distanze_linea_aria_capoluoghi_con_id.csv";

    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Errore apertura file\n";
        return 1;
    }

    const int N = 107; // numero capoluoghi

    // allocazione matrice 2D dinamica
    float** dist = new float*[N + 1];
    for (int i = 0; i <= N; ++i) {
        dist[i] = new float[N + 1];
        for (int j = 0; j <= N; ++j)
            dist[i][j] = 0.0f;
    }

    std::string line;
    std::getline(file, line); // salta intestazione

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string field;

        int origine_id = 0;
        int destinazione_id = 0;
        float km = 0.0f;

        std::getline(ss, field, ',');
        origine_id = std::stoi(field);

        std::getline(ss, field, ',');
        destinazione_id = std::stoi(field);

        // salta origine_capoluogo
        std::getline(ss, field, ',');

        // salta destinazione_capoluogo
        std::getline(ss, field, ',');

        // distanza km
        std::getline(ss, field, ',');
        km = std::stof(field);

        dist[origine_id][destinazione_id] = km;
        dist[destinazione_id][origine_id] = km;
    }

    // esempio accesso
    std::cout << "Distanza 1 -> 2: " << dist[1][2] << " km\n";

    // deallocazione
    for (int i = 0; i <= N; ++i)
        delete[] dist[i];
    delete[] dist;

    return 0;
}