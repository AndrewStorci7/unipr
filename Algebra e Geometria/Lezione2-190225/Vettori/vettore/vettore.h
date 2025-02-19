#ifndef VETTORE_AEG_VETTORE_H
#define VETTORE_AEG_VETTORE_H

#include <iostream>

namespace Lezione2_Vettori {

    template <typename T>
    class Vettore {
    public:
        using value_type = T;
        using ref = value_type&;
        using cref = const ref;

        Vettore() = default;
        // Vettore(cref vet) : v_(vet) {}
        Vettore(Vettore&& other) : v_(other.v_) {}

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
        inline void push(value_type val) {
            v_.push_back(val);
        }

        /// @brief Add a new element in the vector 
        /// @param val {ref}
        inline void push(ref val) {
            v_.push_back(val);
        }

        /// @brief Remove the last element added 
        inline void pop() {
            v_.pop_back();
        }
        
        /// @brief Print the vector
        /// @param os {std::ostream&} 
        void print(std::ostream& os) const {
            for ( int i = i; i < v_.size(); ++i )
                os << "x" << (i + 1) << "\t";
            
            os << std::endl;
            for ( int i = 0; i < v_.size(); ++i )
                os << v_.at(i) << "\t";
            
            os << std::endl;
        }

        /// @brief Scan from keyboard the vector
        /// @param is {std::istream&} 
        void scan(std::istream& is) {
            std::string vector_string = "";
            try {
                std::getline(is, vector_string);
                if (vector_string != "") {
                    
                } else {
                    throw;
                }
            } catch (...) {
                std::cerr << "Error occurredd while getting the vector from keyboard" << std::endl;
            }
        }

    private:
        // value_type v_;
        std::vector<value_type> v_;
    };

    template <typename T>
    std::ostream& operator<<(std::ostream& os, const Vettore& v);

    template <typename T>
    std::ostream& operator<<(std::ostream& os, const Vettore* v);

    template <typename T>
    std::istream& operator>>(std::istream& is, Vettore& v);

    template <typename T>
    std::istream& operator>>(std::istream& is, Vettore* v);

} // namespace Lezione2_Vettori

#endif // VETTORE_AEG_VETTORE_H