#ifndef SHADOW_H
#define SHADOW_H

#include "Component.h"
#include "Sprite.h"
#include "Vec2.h"

class Shadow : public Component {
private:
  Vec2 offset;
  Sprite *sprite;

public:
  Shadow(GameObject &associated, Vec2 offset = Vec2());
  ~Shadow();
  void Update(float dt);
  void UpdatePos(Vec2 footPosition);
  void Render();
  void RequestDelete();
  void SetShadowScale(Vec2 scale);
  bool Is(std::string type);
};

#endif