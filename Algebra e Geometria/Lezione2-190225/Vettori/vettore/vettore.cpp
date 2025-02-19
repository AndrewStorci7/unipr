#include "vettore.h"

namespace Lezione2_Vettori {

    template <typename T>
    std::ostream& operator<<(std::ostream& os, const Vettore<T>& v) {
        v.print(os);
        return os;
    }

    template <typename T>
    std::ostream& operator<<(std::ostream& os, const Vettore<T>* v) {
        v->print(os);
        return os;
    }

    template <typename T>
    std::istream& operator>>(std::istream& is, Vettore<T>& v) {
        v.scan(is);
        return is;
    }

    template <typename T>
    std::istream& operator>>(std::istream& is, Vettore<T>* v) {
        v->scan(is);
        return is;
    }
    
} // namespace Lezione2_Vettori
