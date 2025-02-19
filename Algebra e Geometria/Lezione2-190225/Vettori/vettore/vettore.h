#ifndef VETTORE_AEG_VETTORE_H
#define VETTORE_AEG_VETTORE_H

#include <iostream>
#include <string>
#include <vector>

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

        /// @brief Print the vector
        /// @param os {std::ostream&} 
        void print(std::ostream& os) const {
            for ( int i = 0; i < v_.size(); ++i )
                os << "x" << (i + 1) << "\t";
            
            os << std::endl;
            for ( int i = 0; i < v_.size(); ++i )
                os << v_.at(i) << "\t";
            
            os << std::endl;
        }

        /**
         * Scan from keyboard the vector
         * @param is {std::istream&}
         */
        void scan(std::istream& is) {
            std::string vector_string;
            try {
                std::getline(is, vector_string);
                if (std::cin.fail())
                    throw;
                if (!vector_string.empty()) {
                    auto str_splitted = CF_AEG::split<value_type>(vector_string);
                    // dimension = str_splitted.size();
                    for (auto str : str_splitted)
                        v_.push_back(value_type(str));
                } else {
                    throw;
                }
            } catch (...) {
                std::cerr << "Error occurred while getting the vector from keyboard" << std::endl;
            }
        }

        Vettore&& operator+(const Vettore& other) {
            if (v_.size() != other.v_.size())
                throw std::invalid_argument("vector's dimension are different");

            Vettore ret;
            for ( int i = 0; i < v_.size(); ++i )
                ret.v_.at(i) = v_.at(i) + other.v_.at(i);

            return std::move(ret);
        }

        Vettore& operator=(const Vettore& other) {
            this->v_ = other.v_;
            return *this;
        }

        void operator-(const Vettore& other) {
            if (v_.size() != other.v_.size())
                throw std::invalid_argument("vector's dimension are different");

            auto backup = this->v_;
            for ( int i = 0; i < v_.size(); ++i )
                v_.at(i) = backup.at(i) - other.v_.at(i);
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