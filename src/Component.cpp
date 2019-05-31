#include "Component.h"

Component::Component(GameObject &associated) : associated(associated) {
  this->active = true;
}

Component::~Component() {
}

void Component::Start() {
}

void Component::NotifyCollision(GameObject&) {
}

void Component::Activate() {
  this->active = true;
}

void Component::ToggleActive() {
  this->active = !this->active;
}

void Component::Desactivate() {
  this->active = false;
}

bool Component::IsActive() {
  return this->active;
}