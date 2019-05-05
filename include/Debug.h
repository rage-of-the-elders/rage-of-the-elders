#ifndef DEBUG_H
#define DEBUG_H

#include <iostream>

namespace Debug {
  void DPRINT(std::string s);
  constexpr auto P = DPRINT;

  void DPUTS(std::string s);

  // typeid(*this).name()
  // std::string GetClass(std::string asdf);
}
#endif
