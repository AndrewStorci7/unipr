//
// Created by sandr_ft5c0vu on 11/12/2024.
//

#ifndef CODE_CONSOLE_H
#define CODE_CONSOLE_H

// #include <windows.h>
#include <iostream>

// void enableANSI() {
//     // Ottieni l'handle dello standard output
//     HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
//     if (hOut == INVALID_HANDLE_VALUE) {
//         std::cerr << "Errore: impossibile ottenere l'handle della console.\n";
//         return;
//     }

//     // Attiva il supporto per i codici ANSI
//     DWORD dwMode = 0;
//     if (!GetConsoleMode(hOut, &dwMode)) {
//         std::cerr << "Errore: impossibile leggere la modalità della console.\n";
//         return;
//     }

//     dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
//     if (!SetConsoleMode(hOut, dwMode)) {
//         std::cerr << "Errore: impossibile impostare la modalità della console.\n";
//         return;
//     }
// }

// Codici ANSI per i colori
const std::string RESET = "\033[0m";  // Resetta il colore
const std::string RED = "\033[31m";  // Rosso
const std::string GREEN = "\033[32m";  // Verde
const std::string YELLOW = "\033[33m";  // Giallo
const std::string BLUE = "\033[34m";  // Blu
const std::string MAGENTA = "\033[35m";  // Magenta
const std::string CYAN = "\033[36m";  // Ciano

#endif //CODE_CONSOLE_H
