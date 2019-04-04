#ifndef COMPONENT_H
#define COMPONENT_H

#include <iostream>

class Component {
protected:
  GameObject& associated;

public:
  float x, y;

  Component(GameObject& associated);
  virtual ~Component();
  virtual void Update(float dt) = 0;
  virtual void Render() = 0;
  virtual bool Is(std::string type) = 0;
};

#endif