# Soluzione esercizio risoluzione overloading 09 gennaio 2024

```c++
#include <string>
namespace N {
    struct C {
        std::string& first(); // funzione #1
        const std::string& first() const; // funzione #2
        std::string& last(); // funzione #3
        const std::string& last() const; // funzione #4
    }; // class C

    void bar(double); // funzione #5
    std::string& bar(int); // funzione #6
} // namespace N

void foo(N::C& cm, const N::C& cc) {
    std::string& s1 = cm.first(); // chiamata A
    const std::string& s2 = cm.last(); // chiamata B
    std::string& s3 = cc.first(); // chiamata C
    const std::string& s4 = cc.last(); // chiamata D
    bar(s4.size()); // chiamata E
}
```

```c++
/// Chiamata A
/* Funzioni candidate:
 * - funzione #1
 * - funzione #2
 * 
 * Funzioni utilizzabili: solo la funzione #1 perché s1 (che è la variabile nella quale verrà salvato il dato) non è dichiarato costante
 * Miglior funzione utilizzabile: #1 
 */
 
/// Chiamata B
/* Funzioni candidate:
 * - funzione #3
 * - funzione #4
 * 
 * Funzioni utilizzabili: tutte e due
 * Miglior funzione utlizziabile: #4
 * (NOTA DOPO REVISIONE: la funzione migliore utilizzabile è la #3)
 */
 
/// Chiamata C
/* Funzioni candidate:
 * - funzione #1
 * - funzione #2
 * 
 * Funzioni utlizzabili: nessuna delle due, perché l'oggetto con la quale effettuo la chiamata di first() è constante mentre la variabile s3 non è constante. Perciò non esistono funzioni che corrispondano alla chiamata
 * Errore: undefined reference
 */
 
/// Chiamata D
/* Funzioni candidate:
 * - funzione #3
 * - funzione #4
 * 
 * Funzioni utlizzabili: solo la funzione #4, perché la variabile s4 è dichiarata costante (come il valore di ritorno di last()) e l'oggetto sulla quale avviene la chiamata è costante
 * Miglior funzione utilizzabile: #4
 */
 
/// Chiamata E
/* Funzioni candidate: nessuna
 * Funzioni utilizzabili: nessuna
 * Errore: undefined reference
 */
```