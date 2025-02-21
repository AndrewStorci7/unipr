#include "functions.h"
#include <iostream>
#include <limits>

namespace CF_AEG {

    /**
     * Clear the std::cin buffer to avoid undefined behavior
     */
    void clear_cin_buffer() {
        std::cin.clear ();    // Restore input stream to working state
        std::cin.ignore ( std::numeric_limits<std::streamsize>::max() , '\n' );    // Get rid of any garbage that user might have entered
    }

    /**
     * Check if a string is similar to another avoiding case sensitiveness
     * @param str1 {const std::string&}
     * @param str2 {const std::string&}
     * @return bool
     */
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