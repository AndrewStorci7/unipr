#ifndef VETTORE_AEG_FUNCTIONS_H
#define VETTORE_AEG_FUNCTIONS_H

#include <iostream>
#include <string>
#include <vector>
#include <regex>

namespace CF_AEG {

    extern std::regex regx; // list of character that are not allowed, used for sanitize strings

    /**
     * Sanitize a string from special characters, by default they will be erased.
     * @param str string to sanitize
     * @param replaceWith replace special characters with era <code>replaceWith</code>
     */
    void sstring(std::string& str, char replaceWith = ' ');
    std::string sstring_r(std::string str, char replaceWith = ' ');

    /**
     * Function that split into an array of Ts the string `str` using `delimiter`
     * @param str {`std::string&`}
     * @param delimiter {`const std::string&`}
     * @return {`std::vector<T>`}
     */
    template <typename T>
    std::vector<T>
    split (
        const std::string &str,
        const std::string &delimiter = ","
    ) {

        std::vector<T> str_splitted;
        size_t start = 0, end = 0;

        while (( end = str.find(delimiter, start)) != std::string::npos) {
            const std::string substring = str.substr(start, end - start);
            // auto san_str = sanitizeString(substring); // to fix
            str_splitted.push_back(substring);
            start = end + delimiter.size();
        }
        str_splitted.push_back(str.substr(start));

        return str_splitted;
    }

    /**
     * PROVVISORIA
     * @param str {`std::string&`}
     * @param delimiter {`const std::string&`}
     * @return
     */
    template <>
    inline std::vector<std::string>
    split<std::string> (
        const std::string &str,
        const std::string &delimiter
    ) {
        std::vector<std::string> str_splitted;
        size_t start = 0, end = 0;

        while (( end = str.find(delimiter, start)) != std::string::npos) {
            std::cout << "String to split: \"" << str << "\" ===> ";
            auto substring = str.substr(start, end - start);
            std::cout << "\"" << substring << "\"";
            auto san_str = sstring_r(substring);
            str_splitted.push_back(san_str);
            start = end + delimiter.size();
        }
        str_splitted.push_back(str.substr(start));

        return str_splitted;
    }

    /**
     * Overload of template function `split<T>()` for type `int`
     * @param str {`std::string&`}
     * @param delimiter {`const std::string&`}
     * @return
     */
    template <>
    inline std::vector<int>
    split<int> (
        const std::string &str,
        const std::string &delimiter
    ) {
        std::vector<int> str_splitted;
        size_t start = 0, end = 0;

        while (( end = str.find(delimiter, start)) != std::string::npos) {
            str_splitted.push_back(stoi(str.substr(start, end - start)));
            start = end + delimiter.size();
        }
        str_splitted.push_back(stoi(str.substr(start)));

        return str_splitted;
    }

    /**
     * Overload of template function `split<T>()` for type `double`
     * @param str {`std::string&`}
     * @param delimiter {`const std::string&`}
     * @return
     */
    template <>
    inline std::vector<double>
    split<double> (
        const std::string &str,
        const std::string &delimiter
    ) {
        std::vector<double> str_splitted;
        size_t start = 0, end = 0;

        while (( end = str.find(delimiter, start)) != std::string::npos) {
            str_splitted.push_back(stod(str.substr(start, end - start)));
            start = end + delimiter.size();
        }
        str_splitted.push_back(stod(str.substr(start)));

        return str_splitted;
    }

    /**
     * Clear the std::cin buffer to avoid undefined behavior
     */
    void clear_cin_buffer();

    /**
     * Check if a string is similar to another avoiding case sensitiveness
     * @param str1 {const std::string&}
     * @param str2 {const std::string&}
     * @return
     */
    bool ci_compare(const std::string& str1, const std::string& str2);

}

#endif // VETTORE_AEG_FUNCTIONS_H