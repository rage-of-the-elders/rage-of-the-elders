#include "State.h"

State::State() {
  this->started = false;
  this->popRequested = false;
  this->quitRequested = false;
}

State::~State() {
  this->objectArray.clear();
}

std::weak_ptr<GameObject> State::AddObject(GameObject *object) {
  std::shared_ptr<GameObject> ptr = std::shared_ptr<GameObject>(object);
  this->objectArray.push_back(ptr);

  if (started)
    ptr->Start();
  return ptr;
}

std::weak_ptr<GameObject> State::GetObjectPtr(GameObject *object) {
  for (unsigned i = 0; i < this->objectArray.size(); i++)
    if (this->objectArray[i].get() == object)
      return this->objectArray[i];

  return std::weak_ptr<GameObject>();
}

bool State::PopRequested() {
  return this->popRequested;
}

bool State::QuitRequested() {
  return this->quitRequested;
}

void State::StartArray() {
  for (unsigned i = 0; i < this->objectArray.size(); i++)
    this->objectArray[i]->Start();
}

void State::UpdateArray(float dt) {
  for (unsigned i = 0; i < this->objectArray.size(); i++)
    this->objectArray[i]->Update(dt);
}

void State::RenderArray() {
  GameObject::NewRender(objectArray);
  // for (unsigned i = 0; i < this->objectArray.size(); i++)
  //   this->objectArray[i]->Render();
}

void State::LoadAssets() {}
void State::Update(float) {}
void State::Render() {}
void State::Start() {}
void State::Pause() {}
void State::Resume() {}