//
// Created by andrew on 19/10/24.
//

#include "Matrix.h"

namespace Algebric {

    template<typename T>
    Matrix<T>::Matrix<T>() {
        num_cols_ = 1;
        num_rows_ = 1;
        cols_.resize(num_cols_);
        rows_.resize(num_rows_);
    }

    template<typename T>
    Matrix<T>::Matrix(const size_t& n_cols, const size_t& n_rows)
        : num_cols_(n_cols), num_rows_(n_rows) {

        if (num_cols_ <= 0 || num_rows_ <= 0)
            throw std::invalid_argument("parameters cannot be 0 or null");
        cols_.resize(num_cols_);
        rows_.resize(num_rows_);
    }

    template<typename T>
    Matrix<T>::Matrix(Matrix &&m) {

    }





}