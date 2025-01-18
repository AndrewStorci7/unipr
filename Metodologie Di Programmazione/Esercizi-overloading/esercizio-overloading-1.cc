#include <iostream>

namespace N {

     struct S { S() = default; };

     void foo(int i); // funzione #1

     void foo(double d, S s_obj); // funzione #2

     void bar(const char* pc); // funzione #3

} // namespace N

void bar(char c); // funzione #4

void bar(unsigned long ul); // funzione #5
// void bar(long ul); // funzione #5 TEST

void foo(double d); // funzione #6

void test(const N::S& s_obj) {
     // bar(123); // chiamata A
     // bar("123"); // chiamata B
     foo(4, s_obj); // chiamata C
     N::foo(4.5, s_obj); // chiamata D
}

int main() {

  const N::S s_obj;
  
  test(s_obj);
  return 0;
}
