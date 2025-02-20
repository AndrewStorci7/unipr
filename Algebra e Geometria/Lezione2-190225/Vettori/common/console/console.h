#ifndef CONSOLE_H
#define CONSOLE_H

#include <iostream>
#include <vector>

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"

#define ITALIC  "\033[3m"
#define BOLD    "\033[1m"

/// Console Colorized Coconut
namespace CCC {

    extern std::vector<std::string> colors_string;

    /**
     * Colorize the terminal with the color specified in the param, by default is set to CYAN
     * @param color {std::string}
     * @param rand {const bool}     if specified it will use a random color
     */
    void print_colorized(std::string&& color = "cyan", bool rand = false);
    // static void print_colorized(const char* color);

    /**
     * Reset the color setted in the terminal
     */
    void reset_terminal_color();

    /**
     * Make the font italic
     * @param str
     */
    void italic_font(const std::string& str);

} // namespace CCC

#endif //CONSOLE_H
