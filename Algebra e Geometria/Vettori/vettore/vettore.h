#ifndef VETTORE_AEG_VETTORE_H
#define VETTORE_AEG_VETTORE_H

#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include <cmath>

#include "function.h"

namespace Lezione2_Vettori {

    template <typename T>
    class Vettore {
    public:
        using value_type = T;
        using reference = value_type&;
        // using cref = const reference;

        /**
         * Default constructor
         */
        Vettore() = default;

        /**
         * Copy constructor with vector as a param
         * @param vector
         */
        Vettore(std::vector<value_type>& vector) : v_(vector) {}

        /**
         * Copy constructor with static array as a param
         * @param vector
         */
        Vettore(value_type& vector) {
            for ( auto e : vector )
                v_.push_back(e);
        }

        /**
         * Copy constructor
         * @param vet
         */
        Vettore(const Vettore& vet) : v_(vet.v_) {}

        /**
         * Move constructor
         * @param other
         */
        Vettore(Vettore&& other) noexcept : v_(other.v_) {}

        /**
         * Print the dimension of the vector
         * @return the size (or dimension) of the vector
         */
        std::size_t size() const {
            return v_.size();
        }

        /**
         *
         * @param index
         * @return
         */
        value_type get(const int& index) const {
            value_type ret;
            try {
                ret = v_.at(index);
            } catch (...) {
                ret = 0;
                throw std::invalid_argument("Error occured while accessing position '" + std::to_string(index) + "' on the vector");
            }
            return ret;
        }

        // /**
        //  *
        //  * @param index
        //  * @return
        //  */
        // const reference get(const int& index) const {
        //     try {
        //         const reference ret = v_.at(index);
        //         return ret;
        //     } catch (...) {
        //         std::cerr << "Error occured while accessing position " << index << " on the vector" << std::endl;
        //         return 0;
        //     }
        // }
        
        /// @brief Add a new element in the vector
        /// @param val {value_type} 
        void push(value_type val) {
            v_.push_back(val);
        }

        /// @brief Add a new element in the vector 
        /// @param val {reference}
        void push(reference val) {
            v_.push_back(val);
        }

        /// @brief Remove the last element added 
        void pop() {
            v_.pop_back();
        }

        /// @brief Display more graphically (like a matrix) the vector
        /// @param os {std::ostream&} 
        void display(std::ostream& os) const {
            for ( int i = 0; i < v_.size(); ++i )
                os << "x" << (i + 1) << "\t";
            
            os << std::endl;
            for ( int i = 0; i < v_.size(); ++i )
                os << v_.at(i) << "\t";
        }

        /**
         * Print a simple vector
         * @param os {std::ostream&}
         */
        void print(std::ostream& os) const {
            for ( int i = 0; i < v_.size(); ++i ) {
                if (i == v_.size() - 1)
                    os << v_.at(i);
                else os << v_.at(i) << ", ";
            }
        }

        std::string to_string() const {
            std::string ret;
            for ( int i = 0; i < v_.size(); ++i ) {
                if (i == v_.size() - 1)
                    ret += std::to_string(v_.at(i));
                else ret += std::to_string(v_.at(i)) + ", ";
            }
            return ret;
        }

        /**
         * Check if the string passed to the function it's
         * @param str {std::string}
         */
        void check(std::string& str) {
            if (!str.empty()) {
                auto str_splitted = CF_AEG::split<value_type>(str);
                // dimension = str_splitted.size();
                for (auto str : str_splitted)
                    v_.push_back(value_type(str));
            } else {
                throw std::runtime_error("salamaleku scrivi qualcosa!");
            }
        }

        /**
         * Scan from keyboard the vector
         * @param is {std::istream&}
         */
        void scan(std::istream& is) {
            try {
                // clearing the buffer for secure reason
                CF_AEG::clear_cin_buffer();
                std::cout << "Inserisci il vettore \n[n, n, n, ...]: ";
                std::string vector_string;
                std::getline(is, vector_string);
                if (std::cin.fail())
                    throw std::runtime_error("salamaleku scrivi bene!");

                assert(!std::cin.fail());

                check(vector_string);
            } catch (const std::exception& e) {
                throw;
            }
        }

        Vettore operator+(const Vettore& other) {
            if (v_.size() != other.v_.size())
                throw std::runtime_error("vector's dimension are different");

            Vettore ret;
            ret.v_.resize(v_.size());

            for ( int i = 0; i < v_.size(); ++i )
                ret.v_.at(i) = v_.at(i) + other.v_.at(i);

            return ret;
        }

        Vettore& operator=(const Vettore& other) {
            this->v_ = other.v_;
            return *this;
        }

        Vettore operator-(const Vettore& other) {
            if (v_.size() != other.v_.size())
                throw std::invalid_argument("vector's dimension are different");

            Vettore ret;
            ret.v_.resize(v_.size());

            for ( int i = 0; i < v_.size(); ++i )
                ret.v_.at(i) = v_.at(i) - other.v_.at(i);

            return ret;
        }

        Vettore& operator*(const int& i) {
            for ( auto e : v_ )
                e *= i;

            return *this;
        }

        Vettore& operator*(const double& i) {
            for ( auto e : v_ )
                e *= i;

            return *this;
        }

        Vettore& operator*(const float& i) {
            for ( auto e : v_ )
                e *= i;

            return *this;
        }

//        Vettore operator*(int& i) {
//            for ( auto e : v_ )
//                e *= i;
//
//            return *this;
//        }



        /**
         * Check if Vettore is null
         * @return true if is a vector null <code>{ 0, 0, 0 }</code>
         */
        bool isvectornull() const {
            return std::all_of(v_.begin(), v_.end(), [&](const value_type& val) {
                return val == 0;
            });
        }

    private:
        std::vector<value_type> v_;
        // static size_t dimension;
    };

    /**
     * Prodotto scalare
     * @tparam Number
     * @param left
     * @param right
     * @return
     */
    template <typename Number>
    Number scalar_product(const Vettore<Number>& left, const Vettore<Number>& right) {

        Number ret = 0;
        try {
            if (left.size() != right.size())
                throw std::runtime_error("vector's dimension are different");

            assert(left.size() != 0 and right.size() != 0);

            for (int i = 0; i < left.size(); ++i)
                ret += left.get(i) * right.get(i);
        } catch (const std::invalid_argument& e) {
            ret = 0;
            throw;
        }

        return ret;
    }

    /**
     * Calculate the norma of a vector
     * @tparam Number
     * @param vector
     * @return a new vector <code>Vettore</code>, if teh vector passed as parameter is null, it will return <code>vector</code>
     */
    template <typename Number>
    double norma(const Vettore<Number>& vector) {

        if (vector.isvectornull())
            return -1;

        return std::sqrt(scalar_product(vector, vector));
    }

    /**
     * Prodotto vettoriale, funziona solo su dominio <code>R^3</code>
     * @tparam Number
     * @param left
     * @param right
     * @return
     */
    template <typename Number>
    Vettore<Number> vectorial_product(const Vettore<Number>& left, const Vettore<Number>& right) {

        std::vector<Number> vector = { 0, 0, 0 };
        Vettore<Number> ret = vector;
        if (left.size() > 3 or right.size() > 3)
            return ret;

        vector = {
            (left.get(1) * right.get(2)) - (left.get(2) * right.get(1)),
            (left.get(2) * right.get(0)) - (left.get(0) * right.get(2)),
            (left.get(0) * right.get(1)) - (left.get(1) * right.get(0))
        };
        ret = vector;
        // Vettore<Number> ret;

        return ret;
    }

    template <typename T>
    void operator+=(Vettore<T>& left, const Vettore<T>& right) {
        left + right;
    }

    template <typename T>
    void operator-=(Vettore<T>& left, const Vettore<T>& right) {
        left - right;
    }

    template <typename T>
    std::ostream& operator<<(std::ostream& os, const Vettore<T>&& v) {
        v.print(os);
        return os;
    }

    template <typename T>
    std::ostream& operator<<(std::ostream& os, const Vettore<T>& v) {
        v.print(os);
        return os;
    }

    template <typename T>
    std::ostream& operator<<(std::ostream& os, const Vettore<T>* v) {
        v->print(os);
        return os;
    }

    template <typename T>
    std::istream& operator<<(std::istream& is, Vettore<T>&& v) {
        v.scan(is);
        return is;
    }

    template <typename T>
    std::istream& operator>>(std::istream& is, Vettore<T>& v) {
        v.scan(is);
        return is;
    }

    template <typename T>
    std::istream& operator>>(std::istream& is, Vettore<T>* v) {
        v->scan(is);
        return is;
    }

} // namespace Lezione2_Vettori

#endif // VETTORE_AEG_VETTORE_H