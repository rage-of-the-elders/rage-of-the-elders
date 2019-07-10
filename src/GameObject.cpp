#include "GameObject.h"
#include "Component.h"
#include <algorithm>

GameObject::GameObject() {
  this->isDead = false;
  this->started = false;
  this->angleDeg = 0;
  this->box = Rect();
  this->active = true;
}

GameObject::~GameObject() {
  components.clear();
}

void GameObject::Update(float dt) {
  for (auto &component : components)
    if(component->IsActive())
      component->Update(dt);
}

void GameObject::Render() {

  for (auto &component : components)
    if(component->IsActive())
      component->Render();

  // for (auto &component : components)
  //   allTheGameComponents.push_back(component);
    // if(component->IsActive())   
}

bool SortByY(std::shared_ptr<Component> c1, std::shared_ptr<Component> c2) { 
    return ((c1.get()->GetBox().y) < (c2.get()->GetBox().y)); 
}

void GameObject::NewRender(std::vector <std::shared_ptr<GameObject>> objectArray) {
  std::vector<std::shared_ptr<Component>> allTheGameComponents = std::vector<std::shared_ptr<Component>>();
  std::vector<std::shared_ptr<Component>> fighters = std::vector<std::shared_ptr<Component>>();

  for (unsigned i = 0; i < objectArray.size(); i++) {
    if(objectArray[i]->IsActive())
      if (objectArray[i]->Has("Fighter")) {
        for(auto &component : objectArray[i]->GetComponents())
          fighters.push_back(component);
      } else {
        for(auto &component : objectArray[i]->GetComponents())
          allTheGameComponents.push_back(component);
      }
  }

  std::sort(fighters.begin(), fighters.end(), SortByY);

  for (unsigned i = 0; i < allTheGameComponents.size(); i++)
    if(allTheGameComponents[i]->IsActive())
      allTheGameComponents[i]->Render();

  for (unsigned i = 0; i < fighters.size(); i++)
    if(fighters[i]->IsActive())
      fighters[i]->Render();
}

std::vector<std::shared_ptr<Component>> GameObject::GetComponents() {
  std::vector<std::shared_ptr<Component>> allTheGoComponents = std::vector<std::shared_ptr<Component>>();
  for (unsigned i = 0; i < this->components.size(); i++)
    allTheGoComponents.push_back(this->components[i]);

  return allTheGoComponents;
}

bool GameObject::IsDead() {
  return this->isDead;
}

void GameObject::RequestDelete() {
  this->isDead = true;
}

void GameObject::AddComponent(Component * cpt) {
  this->components.emplace_back(cpt);

  if (this->started)
    cpt->Start();
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

std::vector<std::shared_ptr<Component>> GameObject::GetAllComponent(std::string type) {
  std::vector<std::shared_ptr<Component>> allComponents = std::vector<std::shared_ptr<Component>>();
  for (unsigned i = 0; i < components.size(); i++)
    if (components[i]->Is(type))
      allComponents.push_back(components[i]);
  
  return allComponents;
}

void GameObject::Start() {
  for (auto &obj : this->components)
    obj->Start();

  this->started = true;
}

void GameObject::NotifyCollision(GameObject &other) {
  for(size_t i = 0; i < this->components.size(); i++)
    if(this->components[i]->IsActive())
      this->components[i]->NotifyCollision(other);
}

void GameObject::Activate() {
  this->active = true;
}

void GameObject::Desactivate() {
  this->active = false;
}

bool GameObject::IsActive() {
  return this->active;
}

void GameObject::ToggleActive() {
  this->active = !this->active;
}

bool GameObject::Has(std::string type) {
  return(this->GetComponent(type) != nullptr);
}
