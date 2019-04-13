#include "CameraFollower.h"
#include "Camera.h"

CameraFollower::CameraFollower(GameObject &associated) : Component(associated) {
}

void CameraFollower::Update(float dt) {
  this->associated.box.x = Camera::pos.x;
  this->associated.box.y = Camera::pos.y;
}

void CameraFollower::Render() {
  
}

bool CameraFollower::Is(std::string type) {
  return type == "CameraFollower";
}
