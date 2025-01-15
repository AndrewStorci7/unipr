#ifndef TEMPLATE_CLASS
#define TEMPLATE_CLASS

namespace Lesson19 {

  template <typename T>
  T max(const T& a, const T& b);

  template <typename T>
  T min(const T& a, const T& b);

  template <>
  const char* max(const char* a, const char* b);

} // Lesson19

#endif TEMPLATE_CLASS
