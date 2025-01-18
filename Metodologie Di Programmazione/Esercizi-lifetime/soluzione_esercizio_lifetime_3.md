# Soluzione esercizio lifetime 3 `esercizio_lifetime_3.cc`

```bash
Constructor X::X(globalX)
Constructor X::X(anotherGlobalX)

Start of main
Constructor X::X(localX)

Creating W
Constructor X::X(Y::x1)
Constructor X::X(Y::x2)
Constructor Y::Y()
Constructor X::X(Z::x3)
Constructor Z::Z()
Constructor X::X(W::x4)
Constructor W::W()

Calling createTemporaryX
Constructor X::X(TemporaryX) 
This will likely cause undefined behavior (nope bc I've fixed it): TemporaryX

Destructor W::~W()
Destructor X::~X(W::x4)
Destructor Z::~Z()
Destructor X::~X(Z::x3)
Destructor Y::~Y()
Destructor X::~X(Y::~x2)
Destructor X::~X(Y::~x1)

Destructor X::~X(localX)

End of main

Destructor X::~X(anotherGlobalX)
Destructor X::~X(globalX)
```