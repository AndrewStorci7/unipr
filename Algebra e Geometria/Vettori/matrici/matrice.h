#ifndef VETTORI_MATRICE_H
#define VETTORI_MATRICE_H

#include <vector>
#include "vettore.h"

namespace Lezione3_Matrici {

    template <typename T>
    class Matrice {
    public:

        using value_type = T;
        using reference = value_type&;
        using const_reference = const reference;
        using vettore = Lezione2_Vettori::Vettore<value_type>;

        /**
         * Default constructor
         */
        Matrice() = default;

        /**
         * Move constructor
         * @param other
         */
        Matrice(Matrice&& other) noexcept : matrix_(std::move(other.matrix_)) {}

        /**
         * Copy constructor
         * @param other
         */
        Matrice(const Matrice& other) {
            matrix_.clear(); // Clearing original vector for deep copy
            for (const auto x : other.matrix_ ) {
                matrix_.push_back(x);
            }
        }

        /**
         * Copy constructor
         * @param other
         */
        Matrice(const std::vector<vettore>& other) {
            matrix_.clear();
            for (const auto x : other ) {
                matrix_.push_back(x);
            }
        }

        /**
         * Destructor
         */
        ~Matrice() = default;

        /**
         * Get a Vettore from the matrix
         * @param index
         * @return
         */
        vettore& get(const int& index) {
            try {
                auto ret = matrix_.at(index);
                return ret;
            } catch (...) {
                throw std::runtime_error("Index doesn't exist");
            }
        }

        /**
         * Getter of the matrix
         * @return
         */
        std::vector<vettore>& get() {
            return matrix_;
        }

        /**
         * Push an element on the matrix
         * @param vet Vettore to be pushed
         */
        void push(const vettore& vet) {
            matrix_.push_back(vet);
        }

//        /**
//         * Pull last element inserted
//         */
//        void pull() {
//            matrix_.
//        }

        /**
         * Print the matrix
         */
        void print() const {

        }

        /**
         * Display in a graphic way and more readable a matrix
         */
        void display() const {

        }

        /**
         * Return a string with the same output from `print()`
         * @return
         */
        std::string to_string() const {
            std::string ret;
            return ret;
        }



    private:
        std::vector<vettore> matrix_;

    };

    /**
     * * Find the lambda for the compression of a row in the Gauss algorithm
     * @tparam T
     * @param left The row (`R*`) containing the pivot
     * @param right The row (`R*`) to be compressed
     * @param pivot The pivot
     * @return lamba
     */
    template <typename T>
    double find_lambda(
            const Lezione2_Vettori::Vettore<T>& left,  //
            const Lezione2_Vettori::Vettore<T>& right,
            T pivot
            ) {

        // find the first element != 0
        for ( auto e : right ) {

        }
    }

//    /**
//     *
//     * @tparam T
//     * @param matrix
//     * @return
//     */
//    template <typename T>
//    Lezione2_Vettori::Vettore<T> gauss(
//            Matrice<T>&& matrix
//            ) {
//
//    }

    /**
     *
     * @tparam T
     * @param matrix
     * @return
     */
    template <typename T>
    Lezione2_Vettori::Vettore<T> gauss(
            Matrice<T>& matrix
            ) {

        Lezione2_Vettori::Vettore<T> prova;

        T pivot = 0;                        // pivot
        auto mat = matrix.get();
        size_t m = mat.size();              // height
        size_t n = matrix.get(0).size();    // width
        //
        for ( int i = 0; i < n; ++i ) {
            std::cout << "\n" << i << " ===> ";
            for ( int j = 0; j < m; ++j ) {
                std::cout << mat.at(j) << ", ";
//                if ( mat.at(j) != 0 )
//                    pivot = mat.at(j);
            }
        }

        return prova;
    }

} // Lezione3_Matrici

#endif //VETTORI_MATRICE_H
