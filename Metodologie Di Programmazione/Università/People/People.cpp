//
// Created by andrew-drink on 06/12/24.
//

#include "People.h"

namespace People {

    /**
     * Check if the character is a special character or a digit
     *
     * @param c
     * @return
     */
    inline bool People::is_unwanted_char(char c) {
        return std::ispunct(c) || std::isdigit(c);
    }

    /**
     * Sanitize string.
     * It will delete every character that is not an alphabetic letter
     *
     * @param str
     */
    void People::sanitize_str(std::string& str)  {
        std::string result = input;
        result.erase(std::remove_if(result.begin(), result.end(), is_unwanted_char), result.end());
        str = result;
    }

    /**
     * Copy construcor
     *
     * @param p
     */
    People::People(const People& p) {
        _n = p._n;
        _s = p._s;
    }

    /**
     * Move constructor
     *
     * @param p
     */
    People::People(People&& p) noexcept
    : _n(p._n), _s(p._s) {}

    /**
     * Print the poeple information
     *
     * @param os
     */
    void People::print(ostream& os) {
        os << "name: " << _n << ", surname: " << _s;
    }

    /**
     * Print the poeple information
     *
     * @param os
     */
    void People::scan(ostream& os) const {
        std::string n, s;
        is << "name: " << n;
        is << "surname: " << s;
        _n = n;
        _s = s;
    }

    /**
     * Overload of the output stream operator
     *
     * @param os
     * @param p
     * @return ostream
     */
    ostream& operator<<(ostream& os, const People& p) {
       p.print(os);
       return os;
    }

    /**
     * Overload of the input stream operator
     *
     * @param is
     * @param p
     * @return istream
     */
    istream& operator<<(istream& is, const People& p) {
        p.print(is);
        return is;
    }

} // People