//
// Created by sandr_ft5c0vu on 11/12/2024.
//

#ifndef CODE_CONSOLE_H
#define CODE_CONSOLE_H

#include <windows.h>
#include <iostream>

void enableANSI() {
    // Ottieni l'handle dello standard output
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE) {
        std::cerr << "Errore: impossibile ottenere l'handle della console.\n";
        return;
    }

    // Attiva il supporto per i codici ANSI
    DWORD dwMode = 0;
    if (!GetConsoleMode(hOut, &dwMode)) {
        std::cerr << "Errore: impossibile leggere la modalità della console.\n";
        return;
    }

    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    if (!SetConsoleMode(hOut, dwMode)) {
        std::cerr << "Errore: impossibile impostare la modalità della console.\n";
        return;
    }
}

#endif //CODE_CONSOLE_H
