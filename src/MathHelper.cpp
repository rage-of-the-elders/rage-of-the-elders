#include "MathHelper.h"
#include <iostream>

bool Math::Equals(float a, float b) {
  return (abs(a - b) <= MINIMUM_DIFFERENCE);
}

float Math::Radians(float degree) {
  return (degree * (PI / 180.0));
}

float Math::Degrees(float radians) {
  return (radians * (180.0 / PI));
}

float Math::GetRand(float min, float max) {
  return min + static_cast<float> (rand()) / (static_cast<float>(RAND_MAX / (max - min)));
}
