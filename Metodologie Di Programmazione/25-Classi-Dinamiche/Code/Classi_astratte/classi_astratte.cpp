#include "classi_astratte.h"

namespace ClassiAstratte {

    std::ostream& operator<<(std::ostream& os, const Persona* p) {
        p->print(os);
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const Persona& p) {
        p.print(os);
        return os;
    }

    std::ostream& operator<<(std::ostream& os, Persona* p) {
        p->print(os);
        return os;
    }

    std::ostream& operator<<(std::ostream& os, Persona& p) {
        p.print(os);
        return os;
    }

} // ClassiAstratte