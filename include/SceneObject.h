#ifndef SCENE_OBJECT_H
#define SCENE_OBJECT_H

#include "Component.h"
#include "Sprite.h"
#include "Rect.h"


class SceneObject : public Component {
  private:
    enum SceneObjectState { FROZEN, BROKEN };
    SceneObjectState SceneObjectState;
    std::vector<Sprite*> spriteBrokenObjects;
    std::vector<Sprite*> spriteLivingRoom;
    std::vector<Sprite*> spriteNursery;
    bool isBreakable;
  public:
    SceneObject(GameObject &associated, std::string environment, int x, int y, int objectType);
    void Render();
    void LoadAssets();
    void Update(float dt);
    void NotifyCollision(GameObject &other);
    void BuildObject(std::string environment, int x, int y, int objectType);

    Rect GetColisionRect(int colisionHeigth = 1);
    bool Is(std::string type);
};

#endif
