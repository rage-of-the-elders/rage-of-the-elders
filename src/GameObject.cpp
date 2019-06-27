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

bool ordenateByY(std::shared_ptr<Component> c1, std::shared_ptr<Component> c2) { 
    return ((c1.get()->GetBox().y) < (c2.get()->GetBox().y)); 
}

void GameObject::NewRender(std::vector <std::shared_ptr<GameObject>> objectArray) {
  
  std::vector<std::shared_ptr<Component>> allTheGameComponents = std::vector<std::shared_ptr<Component>>();

  for (unsigned i = 0; i < objectArray.size(); i++)
    for(auto &component : objectArray[i]->GetComponents())
      allTheGameComponents.push_back(component);
  
  // for(auto &component : allTheGameComponents) {
  std::sort(allTheGameComponents.begin(), allTheGameComponents.end(), ordenateByY);
  // }


  for (unsigned i = 0; i < allTheGameComponents.size(); i++)
    if(allTheGameComponents[i]->IsActive())
      allTheGameComponents[i]->Render();
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

bool GameObject::Has(std::string type) {
  return(this->GetComponent(type) != nullptr);
}
