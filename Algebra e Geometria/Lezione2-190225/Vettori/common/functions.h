#ifndef VETTORE_AEG_FUNCTIONS_H
#define VETTORE_AEG_FUNCTIONS_H

#include <iostream>
#include <cstring>
#include <string>
#include <vector>

namespace CF_AEG {

    /**
     * Function that split into an array of string the string `str` using `delimiter`
     * @param str {`std::string&`}
     * @param delimiter {`const std::string&`}
     * @return {`std::string[]`}
     */
    std::vector<std::string> split(const std::string &str, const std::string &delimiter = ", ");

}

#endif // #ifndef VETTORE_AEG_FUNCTIONS_H