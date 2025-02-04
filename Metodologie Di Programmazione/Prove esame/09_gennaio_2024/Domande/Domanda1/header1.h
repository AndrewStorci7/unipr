struct S {
    int i;

    S() = default;
    S(int& i) : i(i) {};
};