#ifndef VETTORI_MATRICE_H
#define VETTORI_MATRICE_H

#include <vector>
#include <algorithm>
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
                vettore& ret = matrix_.at(index);
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
         * Print a simple matrix, used for `operator<<` overload
         * @param os
         */
        void print(std::ostream& os) const {
            for ( auto row : matrix_ ) {
                os << "\t( " << row << " )" << std::endl;
            }
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

        /**
         * Returns the value (element) on a certain block of a matrix
         * @return
         */
        value_type at(const int& column, const int& row) {
            if (row > matrix_.size() or column > matrix_.at(0).size())
                throw std::runtime_error("Out of bound");

            auto row_element = matrix_[row];
            auto value = row_element[column];
            return value;
        }

    private:
        std::vector<vettore> matrix_;

    };

    /**
     * Overload of the `operator<<`
     * @tparam T
     * @param os
     * @param matrix
     * @return
     */
    template <typename T>
    std::ostream& operator<<(
        std::ostream& os,
        const Matrice<T>& matrix
    ) {
        matrix.print(os);
        return os;
    }

    // /**
    //  * Ricerca del pivot (a scalare)
    //  * @tparam T Numeric
    //  * @param matrix Matrice sulla quale effettuare la ricerca
    //  * @param row Riga dalla quale partire
    //  * @param column Colonna dalla quale partire
    //  * @return pivot
    //  */
    // template <typename T>
    // T find_pivot(
    //         Matrice<T>& matrix,
    //         int row,
    //         int column
    // ) {
    //
    //     T pivot = 0; // pivot (di default e' 0)
    //
    //     try {
    //
    //         auto mat = matrix.get();
    //         const size_t m = mat.size();                // height (numero di righe)
    //         // std::cout << m << std::endl;
    //         const size_t n = matrix.get(0).size(); // width (numero di colonne)
    //         // std::cout << n << std::endl;
    //         // Ricerco il primo elemento diverso da 0 (ovvero non nullo)
    //         for ( int i = column; i < n; ++i ) {
    //             // std::cout << "\nColonna " << i << " ===> ";
    //             for ( int j = row; j < m; ++j ) {
    //                 // std::cout << matrix.at(i, j) << ", ";
    //                 if ( matrix.at(i, j) != 0 ) {
    //                     pivot = matrix.at(i, j);
    //                     break;
    //                 }
    //             }
    //             // std::cout << "\nPivot trovato: " << pivot << std::endl;
    //             // assert(pivot == 0);
    //             if (pivot != 0) break;
    //         }
    //     } catch (const std::runtime_error& e) {
    //         throw;
    //     }
    //
    //     return pivot;
    // }

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
            T pivot,
            T rvalue
    ) {
        return (-1 * rvalue) / pivot;
    }

    template <typename T>
    void swap(
        Matrice<T>& matrix,
        Lezione2_Vettori::Vettore<T>& vet,
        int m,
        int i
    ) {

        for ( int j = i; j < m; ++j ) {
            if ( matrix.at(i, j) != 0 ) {
                vet = matrix.get(j);
                std::cout << "R" << j << ":C" << i << " => " << vet << " - [pivot: " << matrix.at(i, j) << "]" << std::endl;

                // scambio la posizione dell'equazione per renderla in scala
                if ( j != i ) {
                    std::cout << "Vettore posizione j:" << j << ": " << *(matrix.get().begin() + j) << std::endl;
                    std::cout << "Vettore posizione i:" << i << ": " << *(matrix.get().begin() + i) << std::endl;
                    std::iter_swap(matrix.get().begin() + j, matrix.get().begin() + i);
                    break;
                }
            }
        }

        std::cout << matrix << std::endl;
    }

    /**
     *
     * @tparam T
     * @param matrix
     * @return
     */
    template <typename T>
    Matrice<T> gauss(
        Matrice<T>& matrix
    ) {

        try {

            auto mat = matrix.get();
            const size_t m = mat.size();                // height (numero di righe)
            const size_t n = matrix.get(0).size(); // width (numero di colonne)

            Lezione2_Vettori::Vettore<T> vet;
            T pivot = 0;
            T lambda = 0;

            for ( int i = 0; i < n; ++i ) {
                swap(matrix, vet, m, i); // sistemo la matrice per metterla in scala
                pivot = vet[i];
                for ( int j = i; j < m; ++j ) {
                    auto val = matrix.at(i, j);
                    if ( j != i and val != 0 ) {
                        lambda = find_lambda(pivot, val);
                        std::cout << "lambda trovato: " << lambda << std::endl;
                        auto lambda_vet = vet * lambda;
                        matrix.get(j) = lambda_vet + matrix.get(j);
                    }
                }

                std::cout << "Matrice dopo iterazione " << i << ": " << std::endl << matrix << std::endl;

            }
        } catch (const std::runtime_error e) {
            // TODO
        }
    }

} // Lezione3_Matrici

#endif //VETTORI_MATRICE_H
