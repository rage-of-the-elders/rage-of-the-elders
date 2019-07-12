#ifndef CAMERA_BARRIER_H
#define CAMERA_BARRIER_H

#include "Component.h"


class CameraBarrier : public Component {
public:
  enum BarrierSide { LEFT_SIDE, RIGHT_SIDE };
  BarrierSide barrierSide;
  CameraBarrier(GameObject &associated, BarrierSide barrierSide, Rect position = Rect());
  void Update(float dt);
  void Render();
  bool Is(std::string type);
  void NotifyCollision(GameObject &other);
};

#endif