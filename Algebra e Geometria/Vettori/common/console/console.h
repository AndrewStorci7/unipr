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

/// Coconut Colorized Console
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
     * Similar to `print_colorized` but it returns a string colorized
     * @param str
     * @param color
     * @param rand
     * @return
     */
    void mk_colorized(std::string&& str, std::string&& color = "cyan", bool rand = false);
    std::string& mk_colorized(std::string& str, std::string&& color = "cyan", bool rand = false);

    /**
     * Reset the color setted in the terminal
     */
    void reset_terminal_color();

    /**
     * Make the font italic
     * @param str
     * @param reset if setted to true it will reset the color
     */
    // std::string mkf_italic(const std::string& str);
    std::string mkf_italic(std::string& str, bool reset = false);
    std::string mkf_italic(std::string&& str, bool reset = false);
    // std::string mkf_italic(const char* str, bool reset = false);

    /**
     * Make the font bold
     * @param str
     */
    // std::string mkf_bold(const std::string& str);
    std::string mkf_bold(std::string& str, bool reset = false);
    std::string mkf_bold(std::string&& str, bool reset = false);
    // std::string mkf_bold(const char* str, bool reset = false);

    /**
     * Clear the console terminal
     */
    void clear_console();

} // namespace CCC

#endif //CONSOLE_H
