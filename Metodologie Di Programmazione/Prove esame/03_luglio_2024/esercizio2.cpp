#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

template <
    typename T 
    // typename U
>
struct IsEqual {

    using value_type = T;
    // using compare_type = U;

    using tref = value_type&;
    using ctref = const tref;

    // using uref = compare_type&;
    // using curef = const uref;

    value_type val_;

    IsEqual(value_type v) : val_(v) {}

    bool operator()(ctref v) {
        return v == val_;
    }

    bool operator()(const char* cc) {
        return strcmp(cc, val_) == 0;
    }
};

template <
    typename InputIt, 
    typename T
>
bool contain_elem(
    InputIt first, InputIt last, 
    const T& val
) {
    for ( ; first != last; ++first) {
        if (*first == val)
            return true;
    }
    return false;
}



template <
    typename InputIt1, 
    typename InputIt2
>
bool contains(
    InputIt1 first1, InputIt1 last1, 
    InputIt2 first2, InputIt2 last2
) {
    for ( ; first2 != last2; ++first2) {
        if (!contain_elem(first1, last1, *first2))
            return false; 
        // IsEqual up(*first2);
        // InputIt1 tmp = first1;
        // bool is_equal = false;
        // for ( ; tmp != last1; ++tmp) {
        //     if (up(*tmp)) {
        //         is_equal = true;
        //         break;
        //     }
        // }
        // if (!is_equal) return false;
    }
    return true;
}

int main() {

    vector<int> vi = {1, 2, 3, 4, 5};
    vector<int> vi2 = {4, 1, 2, 6, 6, 3, 2, 4, 8, 9, 1, 2, 6, 4, 2, 5};
    vector<int> vi3 = {0, 1, 2, 6, 6, 3, 2, 4, 8, 9, 1, 2, 6, 4, 2, 0};
    vector<double> vd = {4.1, 2.6, 6.3, 2.4, 8.9, 1.2, 6.4, 2.5};

    // vector<const char*> vcc = {"prova", "ciao", "pipistrello", "davegay", "mandoancoradipiù"};

    bool check = contains(vi2.begin(), vi2.end(), vi.begin(), vi.end());
    bool check2 = contains(vi3.begin(), vi3.end(), vi.begin(), vi.end());
    bool check3 = contains(vd.begin(), vd.end(), vi.begin(), vi.end());
    // bool check4 = contains(vcc.begin(), vcc.end(), vi.begin(), vi.end());

    cout << "Test 1: " << (check ? "Corretto" : "Sbagliato") << endl;
    cout << "Test 2: " << (check2 ? "Corretto" : "Sbagliato") << endl;
    cout << "Test 3: " << (check3 ? "Corretto" : "Sbagliato") << endl;
    // cout << "Test 4: " << (check4 ? "Corretto" : "Sbagliato") << endl;

    return 0;
}