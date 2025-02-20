#include "console.h"
#include "functions.h"

namespace CCC {

    /// Default list of available colors
    std::vector<std::string> colors_string = { "cyan", "red", "blue", "green", "yellow", "magenta", "white" };

    void print_colorized(std::string&& color, const bool rand) {
        using CF_AEG::caseInsensitiveCompare;

        // if rand is set to true it will set a random color
        if (rand)
            color = colors_string.at(std::rand() % colors_string.size());

        if (caseInsensitiveCompare(color, "cyan"))
            std::cout << CYAN;
        else if (caseInsensitiveCompare(color, "red"))
            std::cout << RED;
        else if (caseInsensitiveCompare(color, "green"))
            std::cout << GREEN;
        else if (caseInsensitiveCompare(color, "blue"))
            std::cout << BLUE;
        else if (caseInsensitiveCompare(color, "yellow"))
            std::cout << YELLOW;
        else if (caseInsensitiveCompare(color, "magenta"))
            std::cout << MAGENTA;
        else if (caseInsensitiveCompare(color, "white"))
            std::cout << WHITE;
        else
            std::cout << CYAN;
    }

    void reset_terminal_color() {
        std::cout << RESET;
    }

    void italic_font(const std::string& str) {
        std::cout << ITALIC << str << RESET;
    }
}
