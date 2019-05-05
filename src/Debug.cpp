#include <iostream>
#include "Debug.h"

namespace Debug {
  void DPRINT(std::string s) {
    printf("[DEBUG] %s", s.c_str());
  }
  void DPUTS(std::string s) {
    DPRINT(s + "\n");
  }

  // std::string DCLASS(std::string functionName) {
  //   std::string klass = functionName.substr(0, functionName.find("::"));

  //   if(klass.find(" ") != std::string::npos) {
  //     klass.substr(functionName.find(" "), functionName.size() - 1).erase(0, 1);
  //   }
    
  //   return klass;
  // }

  // void DebugMsg(std::string functionName, std::string msg) {
  //   DPRINT(GetClass(functionName) + " " + msg);
  // }
}