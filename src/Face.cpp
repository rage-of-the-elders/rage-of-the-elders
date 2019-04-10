#include "Face.h"
#include "Sound.h"
#include "InputManager.h"

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
      sound->Play(1);
  }
}

void Face::Update(float dt) {
    if (InputManager::GetInstance().MousePress(LEFT_MOUSE_BUTTON)) {
      if (this->associated.box.Contains( (float)InputManager::GetInstance().GetMouseX(),
                                         (float)InputManager::GetInstance().GetMouseY() ) ) {
          float damage = std::rand() % 10 + 10;
          this->Damage(damage);
      }
  }
}

void Face::Render() {
  
}

bool Face::Is(std::string type) {
  return type == "Face";
}

bool Face::IsDead() {
  return this->hitpoints <= 0;
}
