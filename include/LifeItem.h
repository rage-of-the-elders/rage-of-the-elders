#ifndef LIFE_ITEM_H
#define LIFE_ITEM_H

#include "Component.h"
#include "Sound.h"

class LifeItem : public Component {
  private:
    std::vector<std::string> itensNames;
    float x;
    float y;
    Sound *itemPickup;
  public:
    LifeItem(GameObject &associated, float x, float y);
    void Update(float dt);
    void Render();
    bool Is(std::string type);
    void NotifyCollision(GameObject &other);
};

#endif