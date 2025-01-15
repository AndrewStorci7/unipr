//
// Created by andrew-drink on 15/01/25.
//

#ifndef TEMPLATE_1_TEMPLATE_H
#define TEMPLATE_1_TEMPLATE_H

#include <cstring>

namespace Lesson19 {

    template <typename T>
    inline T max(const T& a, const T& b) {
        return (a > b) ? a : b;
    }

    template <typename T>
    const char* max(const char* a, const char* b) {
        return (strcmp(a, b) > 0) ? b : a;
    }

    template <typename T>
    inline T min(const T& a, const T& b) {
        return not max(a, b);
    }

} // namespace Lesson19

#endif //TEMPLATE_1_TEMPLATE_H
