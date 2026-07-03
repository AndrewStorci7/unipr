/**
 * Consegna 6
 * @author Andrea Storci
 */

#include <iostream>
#include <fstream>

#include "functions/needleman_wunsch.h"

using namespace std;

int main(int argc, char* argv[]) {
	// std::ofstream fout;
	// std::streambuf* stream_buffer_cout = std::cout.rdbuf(); // Salva il buffer originale (terminale)
	//
	// if (argc > 1) {
	// 	fout.open(argv[1]);
	// 	if (fout.is_open()) {
	// 		std::cout.rdbuf(fout.rdbuf());
	// 	} else {
	// 		std::cerr << "Errore nell'apertura del file!" << std::endl;
	// 		return 1;
	// 	}
	// }

	needlemanWunsch("source2.cpp", "test002.cpp");

	// if (fout.is_open()) {
	// 	std::cout.rdbuf(stream_buffer_cout);
	// 	fout.close();
	// }

	return 0;
}

