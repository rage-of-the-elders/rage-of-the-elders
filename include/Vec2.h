#ifndef VEC2_H
#define VEC2_H

#include "MathHelper.h"

class Vec2 {
public:
  float x, y;

  Vec2();
  Vec2(float x, float y);
  static float Cos(float angle);
  static float Sin(float angle);
  static float Acos(float angle);
  static float Atan2(float a, float b);
  Vec2 Rotate(float distance = 0, float angle = 0);
  float GetDeltaX(float targetX);  
  float GetDeltaY(float targetY);
  float GetDistance(Vec2 target);
  float GetModule();
  static float Module(float x, float y);
  float GetAngle(Vec2 target);
  Vec2 GetSpeed(Vec2 pos);
  static Vec2 GetSpeed(float angle);

  Vec2 operator+(const Vec2 &other) const;
  Vec2 operator+(const float other) const;
  Vec2 operator-(const Vec2 &other) const;
  Vec2 operator-(const float other) const;
  Vec2 operator*(const float other) const;
  float operator*(const Vec2 &other) const; // Dot product
};

#endif