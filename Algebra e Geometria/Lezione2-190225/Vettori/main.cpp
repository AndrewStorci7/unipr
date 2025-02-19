#include <iostream>
#include <map>
#include "common/start/start.h"

int main() {

    using START_AEG::map_v;

    map_v v_vettori;

    START_AEG::start(std::move(v_vettori));

    return 0; // end of the program, bye bye, salamaleku
}
