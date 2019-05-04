#ifndef MATH_HELPER_H
#define MATH_HELPER_H
#define PI 3.1415926535
#define MINIMUM_DIFFERENCE 1e-6

class Math {
public:
  static bool Equals(float a, float b);
  static float Radians(float degree);
  static float Degrees(float radians);
};

#endif