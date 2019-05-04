#include "Math.h"
#include <iostream>

bool Math::equals(float a, float b) {
  return (abs(a - b) <= MINIMUM_DIFFERENCE);
}
