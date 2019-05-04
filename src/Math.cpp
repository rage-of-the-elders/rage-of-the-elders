#include "Math.h"
#include <iostream>

bool Math::Equals(float a, float b) {
  return (abs(a - b) <= MINIMUM_DIFFERENCE);
}
float Math::Radians(float degree) {
  return (degree * (PI / 180.0));
}
