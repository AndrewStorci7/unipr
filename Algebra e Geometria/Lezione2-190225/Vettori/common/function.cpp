#include "functions.h"
#include <iostream>
#include <limits>

namespace CF_AEG {

    /**
     * NOT WORKING!!!
     * Clear the console terminal
     */
    void clear_console() {
#if defined _WIN32
        system("cls");
        //clrscr(); // including header file : conio.h
#elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
        system("clear");
        std::cout<< u8"\033[2J\033[1;1H"; //Using ANSI Escape Sequences
#elif defined (__APPLE__)
        system("clear");
#endif
    }

    /**
     * Clear the std::cin buffer to avoid undefined behavior
     */
    void clear_cin_buffer() {
        std::cin.clear ();    // Restore input stream to working state
        std::cin.ignore ( std::numeric_limits<std::streamsize>::max() , '\n' );    // Get rid of any garbage that user might have entered
    }

    bool caseInsensitiveCompare(const std::string& str1, const std::string& str2) {
        if (str1.length() != str2.length()) return false;

        return std::equal(
            str1.begin(), str1.end(),
            str2.begin(),
            [](const char a, const char b) {
                return std::tolower(a) == std::tolower(b);
            }
        );
    }

} // namespace CF_AEG