//
// Created by andrew on 18/10/24.
//
#pragma once

#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <vector>

namespace Algebric {
    class Matrix {
        // using ntot = int;
        using cols = std::vector<std::string>;
        using rows = std::vector<int>;
    private:
        size_t num_cols_;
        size_t num_rows_;
        cols cols_;
        rows rows_;

        Matrix();

        Matrix()
    };
}

#endif //MATRIX_H
