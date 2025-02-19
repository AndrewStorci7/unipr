#include "functions.h"

namespace CF_AEG {

    std::vector<std::string> split(std::string &str, const std::string &delimiter) {
        std::vector<std::string> str_splitted;
        size_t pos = 0;
        std::string token = "";
        for ( int i = 0; i < str.size(); ++i ) {
            pos = str.find(delimiter);
            token = str.substr(0, pos);
            str.erase(0, pos + delimiter.size());
            str_splitted.push_back(token);
        }
        str_splitted.push_back(token);

        return str_splitted;
    }

} // namespace CF_AEG