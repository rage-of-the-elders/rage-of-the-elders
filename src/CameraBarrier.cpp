#include "CameraBarrier.h"
#include "Collider.h"

CameraBarrier::CameraBarrier(GameObject &associated, BarrierSide barrierSide, Rect position) : Component(associated) {
  this->associated.box = position;
  this->associated.AddComponent(new Collider(this->associated));
  this->barrierSide = barrierSide;
}

void CameraBarrier::Update(float) {}

void CameraBarrier::Render() {

}

bool CameraBarrier::Is(std::string type) {
  return(type == "CameraBarrier");
}

void CameraBarrier::NotifyCollision(GameObject&) {}