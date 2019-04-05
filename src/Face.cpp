#include "Face.h"
#include "Sound.h"

Face::Face(GameObject &associated) : Component(associated) {
  this->hitpoints = 30;
}

Face::~Face() {}

void Face::Damage(int damage) {
  this->hitpoints -= damage;
  if (this->IsDead()) {
    this->associated.RequestDelete();

    Sound *sound = (Sound *) this->associated.GetComponent("Sound");
    if (sound != nullptr)
      sound->Play();
  }
}
void Face::Update(float dt) {}
void Face::Render() {}

bool Face::Is(std::string type) {
  return type == "Face";
}

bool Face::IsDead() {
  return this->hitpoints <= 0;
}
