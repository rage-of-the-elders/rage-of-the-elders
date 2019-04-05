#ifndef VEC2_H
#define VEC2_H
#define PI 3.1415926535

class Vec2 {
public:
  float x, y;

  Vec2();
  Vec2(float x, float y);
  float Cos(float angle);
  float Sin(float angle);
  Vec2 Rotate(float angle);

  Vec2 operator+(const Vec2 &other) const;
  Vec2 operator+(const float other) const;
  Vec2 operator-(const Vec2 &other) const;
  Vec2 operator-(const float other) const;
  Vec2 operator*(const float other) const;
};

#endif