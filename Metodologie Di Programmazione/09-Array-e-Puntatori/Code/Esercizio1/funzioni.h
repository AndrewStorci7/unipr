//
// Created by andrew-drink on 20/12/24.
//

#ifndef ESERCIZIO1_FUNZIONI_H
#define ESERCIZIO1_FUNZIONI_H

#include <iostream>
#include <ctime>
#include <cstdlib>

namespace ArrayVsPuntatori {

//    void swap(int a[]) {
//        for (int i = 0; i < )
//    }

//    void pswap(int* a) {
//        for ()
//    }

    template <typename T>
    size_t size(const T& obj) {
        return (sizeof obj / sizeof *obj);
    }

    template <typename T>
    void mod(T* obj, size_t size) {
        srand(time(NULL));
        for (T* p = obj; p != obj + size; ++p)
            *p = *p + (rand() % 11 + 10);
    }

    template <typename T>
    void print(const T* obj, size_t size) {
        std::cout << "[";
        for (const T* p = obj; p != obj + size; ++p) {
            if (p == (obj + size) - 1)
                std::cout << *p << "]" << std::endl;
            else std::cout << *p << ", ";
        }
    }
}

#endif //ESERCIZIO1_FUNZIONI_H
