#ifndef CAMERAFOLLOWER_H
#define CAMERAFOLLOWER_H

#include "GameObject.h"
#include "Component.h"

class CameraFollower : public Component {
public:
  Vec2 offset;
  bool centered;

  CameraFollower(GameObject &associated, Vec2 offset = {0, 0}, bool centered = false);
  void Update(float dt);
  void Render();
  bool Is(std::string type);
};

#endif