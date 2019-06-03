#ifndef MATH_HELPER_H
#define MATH_HELPER_H
#define PI 3.1415926535
#define MINIMUM_DIFFERENCE 1e-6

class Math {
public:
  static bool Equals(float a, float b);
  static bool IsClose(float a, float b, float difference);
  static float Radians(float degree);
  static float Degrees(float radians);
  static float GetRand(float min, float max);
  static bool InRange(float value, float min, float max);
};

#endif