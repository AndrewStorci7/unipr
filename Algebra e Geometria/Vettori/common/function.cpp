#include "functions.h"
#include <iostream>
#include <limits>

namespace CF_AEG {

    std::regex regx("[@!#$%^&*()?/|}{~: ]"); // list of character that are not allowed, used for sanitize strings

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
    bool ci_compare(const std::string& str1, const std::string& str2) {
        if (str1.length() != str2.length()) return false;

        return std::equal(
            str1.begin(), str1.end(),
            str2.begin(),
            [](const char a, const char b) {
                return std::tolower(a) == std::tolower(b);
            }
        );
    }

    /**
     * Sanitize a string from special characters, by default they will be erased.
     * @param str string to sanitize
     * @param replaceWith replace special characters with era <code>replaceWith</code>
     */
    void sstring(std::string& str, const char replaceWith) {

        // TODO: da testare
        // if (std::regex_search(std::to_string(replaceWith), regx) == 0)
        //     replaceWith = '';
        std::cout << "Initial string: " << str << " => ";

        str.erase(std::remove_if(str.begin(), str.end(), [](char c) {
            return !std::isalnum(c); // Remove if NOT a letter or digit
        }), str.end());

        std::cout << "\"" << str << "\"" << std::endl;
    }

    /**
     * Sanitize a string from special characters, by default they will be erased.
     * @param str string to sanitize
     * @param replaceWith replace special characters with <code>replaceWith</code>, default is <b>empty</b> char
     * @return the same string <code>str</code> but sanitized
     */
    std::string sstring_r(std::string str, const char replaceWith) {

        // TODO: da testare
        // if (std::regex_search(std::to_string(replaceWith), regx) == 0)
        //     replaceWith = '';

        sstring(str, replaceWith);
        return str;
    }

} // namespace CF_AEG