//
// Created by andrew on 18/10/24.
//
#pragma once

#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <vector>

namespace Algebric {

    template
    <typename T>
    class Matrix {
        // using ntot = int;
        using cols = std::vector<std::string>;
        using rows = std::vector<T>;
    private:
        size_t num_cols_;
        size_t num_rows_;
        cols cols_;
        rows rows_;

        /**
         * Default Constructor with 0 params
         */
        Matrix();

        /**
         * Matrix Constructor with 2 param:
         *    n_cols | total number of rows
         *    n_rows | total number of columns
         *
         * @param n_cols
         * @param n_rows
         */
        Matrix(size_t n_cols, size_t n_rows);

        /**
         * Move Matrix Constructor
         *
         * @param m
         */
        Matrix(Matrix&& m);

        /**
         * Getter
         *
         * @param c
         * @param n
         * @return T
         */
        T& get(const size_t& c, const size_t& n) const;

        /**
         * Setter
         * @param c
         * @param n
         */
        void set(const size_t& c, const size_t& n);

        /**
         * Print the matrix
         *
         * @param os
         * @param m
         */
        void print(ostream& os, const Matrix& m) const;

        /**
         * Move a data from a cell to another
         *
         * @param row_from
         * @param col_from
         * @param row_to
         * @param col_to
         */
        void move(const size_t& row_from, const size_t& col_from, const size_t& row_to, const size_t& col_to);
    };
}

#endif //MATRIX_H
