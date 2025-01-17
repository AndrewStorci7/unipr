//
// Created by andrew-drink on 15/01/25.
//

#ifndef TEMPLATE_1_TEMPLATE_H
#define TEMPLATE_1_TEMPLATE_H

#include <cstring>

namespace Lesson19 {

    template <typename T>
    inline T max(T a, T b) {
        return (a > b) ? a : b;
    }

    template <>
    const char* max(const char* a, const char* b) {
        return (strcmp(a, b) > 0) ? b : a;
    }

} // namespace Lesson19

#endif //TEMPLATE_1_TEMPLATE_H
