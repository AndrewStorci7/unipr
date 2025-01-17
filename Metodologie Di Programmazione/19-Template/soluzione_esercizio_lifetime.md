# Soluzione output `esercizio_lifetime.cc`

```bash
// Chiamata da C3 c3
Constructor C1::C1();
Constructor C3::C3();

// Chiamata da C1 c1
Constructor C1::C1();

/// Chiamata all'interno di main()
Start

// Chiamata da C1 c1 all'interno del blocco try & catch
Constructor C1::C1();

// Chiamata da D d all'interno del blocco try & catch
Constructor C1::C1();
Constructor C1::C1();
Constructor C2::C2();
...
Destructor C1::~C1();
Destructor C1::~C1();
Destructor C2::~C2();
Destructor D::~D();
End
Destructor C1::~C1();
Destructor C3::~C3();
```


