#ifndef COLLIDER_H
#define COLLIDER_H

#include "Component.h"
#include <string>

class Collider : public Component {
private:
  Vec2 scale;
  Vec2 offset;
  int colliderType;

public:
  Rect box;

  Collider(GameObject &associated, Vec2 scale = {1, 1}, Vec2 offset = {0, 0}, int colliderType = 0);
  void Update(float dt);
  void Render();
  float GetWidth();
  float GetHeigth();
  float GetX();
  float GetY();
  bool Is(std::string type);
  void SetScale (Vec2 scale);
  void SetOffset (Vec2 offset);
  Vec2 GetOffset ();
  void SetColliderType(int type);
  int GetColliderType();
};

#endif