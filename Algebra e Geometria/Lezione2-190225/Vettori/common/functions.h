#ifndef VETTORE_AEG_FUNCTIONS_H
#define VETTORE_AEG_FUNCTIONS_H

#include <iostream>
#include <cstring>
#include <string>
#include <vector>

namespace CF_AEG {

    /**
     * Function that split into an array of numbers the string `str` using `delimiter`
     * @param str {`std::string&`}
     * @param delimiter {`const std::string&`}
     * @return {`std::vector<Number>`}
     */
    template <typename Number>
    std::vector<Number>
    split (
        const std::string &str,
        const std::string &delimiter = ", "
    ) {

        std::vector<Number> str_splitted;
        size_t start = 0, end = 0;

        while (( end = str.find(delimiter, start)) != std::string::npos) {
            str_splitted.push_back(Number(str.substr(start, end - start)));
            start = end + delimiter.size();
        }
        str_splitted.push_back(Number(str.substr(start)));

        return str_splitted;
    }

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

}

#endif // #ifndef VETTORE_AEG_FUNCTIONS_H