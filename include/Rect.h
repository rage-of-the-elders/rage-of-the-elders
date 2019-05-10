#ifndef RECT_H
#define RECT_H

#include "Vec2.h"

class Rect {
public:
  float x, y, w, h;

  Rect();
  Rect(float x, float y, float w, float h);
  bool Contains(float x, float y);
  Vec2 GetPos();
  Vec2 GetCenter();
  void SetPos(float x, float y);
  void SetPos(Vec2 pos);
  void UpdatePos(Vec2 pos);
  void SetCenterPos(float centerX, float centerY);
  void SetCenterPos(Vec2 center);
  void SetSize(float w, float h);
  void SetSize(Vec2 size);
};

#endif