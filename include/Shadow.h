#ifndef SHADOW_H
#define SHADOW_H

#include "Component.h"

class Shadow : public Component {
private:
  Vec2 offset;

public:
  Shadow(GameObject &associated, Vec2 offset = Vec2());
  ~Shadow();
  void Update(float dt);
  void UpdatePos(Vec2 footPosition);
  void Render();
  void RequestDelete();
  bool Is(std::string type);
};

#endif