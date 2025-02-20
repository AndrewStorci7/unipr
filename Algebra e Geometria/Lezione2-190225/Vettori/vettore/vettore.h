#ifndef VETTORE_AEG_VETTORE_H
#define VETTORE_AEG_VETTORE_H

#include <iostream>
#include <string>
#include <vector>
#include <cassert>

#include "functions.h"

namespace Lezione2_Vettori {

    template <typename T>
    class Vettore {
    public:
        using value_type = T;
        using ref = value_type&;
        using cref = const ref;

        Vettore() = default;
        Vettore(const Vettore& vet) : v_(vet.v_) {}
        Vettore(Vettore&& other) noexcept : v_(other.v_) {}

        ref get(const int& index) {
            try {
                ref ret = v_.at(index);  
                return ret;
            } catch (...) {
                std::cerr << "Error occured while accessing position " << index << " on the vector" << std::endl;
                return 0;
            }
        }

        cref get(const int& index) const {
            try {
                cref ret = v_.at(index);
                return ret;
            } catch (...) {
                std::cerr << "Error occured while accessing position " << index << " on the vector" << std::endl;
                return 0;
            }
        }
        
        /// @brief Add a new element in the vector
        /// @param val {value_type} 
        void push(value_type val) {
            v_.push_back(val);
        }

        /// @brief Add a new element in the vector 
        /// @param val {ref}
        void push(ref val) {
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

        // static size_t dimension() {
        //     return v_.size();
        // }

    private:
        std::vector<value_type> v_;
        // static size_t dimension;
    };

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