# Soluzione esercizio 2 `esercizio_lifetime_2.cc`

```bash
Constructor A::A(globalA)
Constructor A::A(anotherGlobalA)
Start of main

Constructor A::A(localA)
Constructor A::A(B::a1)
Constructor A::A(B::a2)
Constructor B::B()

Creating object D

Constructor A::A(D::a4)
Constructor A::A(B::a1)
Constructor A::A(B::a2)
Constructor B::B()
Constructor A::A(B::a1)
Constructor A::A(B::a2)
Constructor B::B()
Constructor A::A(C::a3)
Constructor C::C()
Destructor A::A(localA)
Destructor A::A(B::a1)
Destructor A::A(B::a2)
Destructor B::B()

Destructor A::A(D::a4)
Destructor A::A(B::a1)
Destructor A::A(B::a2)
Destructor B::B()
Destructor A::A(B::a1)
Destructor A::A(B::a2)
Destructor B::B()
Destructor A::A(C::a3)

Caught std::runtime_error: Error in C constructor



```