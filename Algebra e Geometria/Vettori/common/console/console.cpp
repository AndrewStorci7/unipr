#include "console.h"
#include "functions.h"

namespace CCC {

    /// Default list of available colors
    std::vector<std::string> colors_string = { "cyan", "red", "blue", "green", "yellow", "magenta", "white" };

    /**
     * Colorize the terminal with the color specified in the param, by default is set to CYAN
     * @param color name of the color, default is <b>cyan</b>
     * @param rand  if set to <code>true</code> it will pick a random color
     */
    void print_colorized(std::string&& color, const bool rand) {
        using CF_AEG::ci_compare;

        // if rand is set to true it will set a random color
        if (rand)
            color = colors_string.at(std::rand() % colors_string.size());

        if (ci_compare(color, "cyan"))
            std::cout << CYAN;
        else if (ci_compare(color, "red"))
            std::cout << RED;
        else if (ci_compare(color, "green"))
            std::cout << GREEN;
        else if (ci_compare(color, "blue"))
            std::cout << BLUE;
        else if (ci_compare(color, "yellow"))
            std::cout << YELLOW;
        else if (ci_compare(color, "magenta"))
            std::cout << MAGENTA;
        else if (ci_compare(color, "white"))
            std::cout << WHITE;
        else
            std::cout << CYAN;
    }

    /**
     * Similar to <code>print_colorized</code>, but it returns a string colorized
     * @param str   string to be colored
     * @param color name of the color, default is <b>cyan</b>
     * @param rand  if set to <code>true</code> it will pick a random color
     */
    void mk_colorized(std::string&& str, std::string&& color, const bool rand) {
        using CF_AEG::ci_compare;

        // if rand is set to true it will set a random color
        if (rand)
            color = colors_string.at(std::rand() % colors_string.size());

        if (ci_compare(color, "cyan"))
            str = CYAN + str + RESET;
        else if (ci_compare(color, "red"))
            str = RED + str + RESET;
        else if (ci_compare(color, "green"))
            str = GREEN + str + RESET;
        else if (ci_compare(color, "blue"))
            str = BLUE + str + RESET;
        else if (ci_compare(color, "yellow"))
            str = YELLOW + str + RESET;
        else if (ci_compare(color, "magenta"))
            str = MAGENTA + str + RESET;
        else if (ci_compare(color, "white"))
            str = WHITE + str + RESET;
        else
            str = CYAN + str + RESET;
    }

    /**
     * Similar to <code>print_colorized</code>, but it returns a string colorized
     * @param str   string to be colored
     * @param color name of the color, default is <b>cyan</b>
     * @param rand  if set to <code>true</code> it will pick a random color
     * @return same string passed as parameter, but colorized
     */
    std::string& mk_colorized(std::string& str, std::string&& color, const bool rand) {
        using CF_AEG::ci_compare;

        // if rand is set to true it will set a random color
        if (rand)
            color = colors_string.at(std::rand() % colors_string.size());

        if (ci_compare(color, "cyan"))
            str = CYAN + str + RESET;
        else if (ci_compare(color, "red"))
            str = RED + str + RESET;
        else if (ci_compare(color, "green"))
            str = GREEN + str + RESET;
        else if (ci_compare(color, "blue"))
            str = BLUE + str + RESET;
        else if (ci_compare(color, "yellow"))
            str = YELLOW + str + RESET;
        else if (ci_compare(color, "magenta"))
            str = MAGENTA + str + RESET;
        else if (ci_compare(color, "white"))
            str = WHITE + str + RESET;
        else
            str = CYAN + str + RESET;

        return str;
    }

    void reset_terminal_color() {
        std::cout << RESET;
    }

    std::string mkf_italic(std::string& str, bool reset) {
        return ITALIC + str + RESET;
    }

    std::string mkf_italic(std::string&& str, bool reset) {
        return ITALIC + str + RESET;
    }

    std::string mkf_bold(std::string& str, bool reset) {
        return BOLD + str + RESET;
    }

    std::string mkf_bold(std::string&& str, bool reset) {
        return BOLD + str + RESET;
    }

    /**
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

}
