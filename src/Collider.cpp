#include "Collider.h"

Collider::Collider(GameObject &associated, Vec2 scale, Vec2 offset) : Component(associated) {
  this->scale = scale;
  this->offset = offset;
}

void Collider::Update(float dt) {
  // Depois, faça com que o centro 
  // dela seja igual ao centro da box de associated, adicionado do atributo offset
  // rotacionado pelo ângulo de associated.

  this->box.SetSize(this->associated.box.w * this->scale.x,
                    this->associated.box.h * this->scale.y);
  this->box.SetCenterPos((this->associated.box.GetCenter() + this->offset).Rotate(this->associated.angleDeg)); // TODO: CHECK THIS

}

void Collider::Render() {

}

bool Collider::Is(std::string type) {
  return type == "Collider";
}

void Collider::SetScale(Vec2 scale) {
  this->scale = scale;
}

void Collider::SetOffset(Vec2 offset) {
  this->offset = offset;
}
