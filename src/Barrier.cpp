#include "Barrier.h"
#include "Collider.h"

Barrier::Barrier(GameObject &associated, Rect position) : Component(associated) {
  this->associated.box = position;
  this->associated.AddComponent(new Collider(this->associated));
}

void Barrier::Update(float dt) {

}

void Barrier::Render() {

}

bool Barrier::Is(std::string type) {
  return(type == "Barrier");
}

void Barrier::NotifyCollision(GameObject &other) {

}