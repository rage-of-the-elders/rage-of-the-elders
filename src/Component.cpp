#include "Component.h"

Component::Component(GameObject &associated) : associated(associated) {
}

Component::~Component() {
}

void Component::Start() {
}

void Component::NotifyCollision(GameObject &other) {
}

void Component::Activate() {
  this->active = true;
}

void Component::Desactivate() {
  this->active = false;
}

bool Component::IsActive() {
  return this->active;
}