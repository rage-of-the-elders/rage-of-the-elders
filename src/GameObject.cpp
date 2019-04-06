#include "GameObject.h"
#include "Component.h"

GameObject::GameObject() {
  this->isDead = false;
}

GameObject::~GameObject() {
  components.clear();
}

void GameObject::Update(float dt) {
  for (auto &component : components)
    component->Update(dt);
}

void GameObject::Render() {
  for (auto &component : components)
    component->Render();
}

bool GameObject::IsDead() {
  return this->isDead;
}

void GameObject::RequestDelete() {
  this->isDead = true;
}

void GameObject::AddComponent(Component * cpt) {
  this->components.emplace_back(cpt);
}

void GameObject::RemoveComponent(Component *cpt) {
  for (int i = components.size() - 1; i >= 0; i--)
    if (components[i].get() == cpt)
      components.erase(components.begin() + i);
}

Component *GameObject::GetComponent(std::string type) {
  for (unsigned i = 0; i < components.size(); i++)
    if (components[i]->Is(type))
      return components[i].get();
  return nullptr;
}